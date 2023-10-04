#include "api.h"
#include <QtDebug>

API::API ( QString portname, int baudrate) : QThread()
{
    myPortName = portname;
    serial.setPortname(portname);
    serial.setBaudrate(baudrate);

    settings_set = 1;
    get_settings_confirmed=0;
    notification_request_confirmed=0;
    dpr_flag = 0;
    temp_dp_value = 0;
    temp_dp_value_flag = 0;

    _index = 0;
    _in_progress = 0;
    _ndx=0;
    _op_code = 255;
    _message_length = 0;

    _cycle_period=30; // api run method should take 30 ms each cycle

    m_currentDevices = devices();

    _signal_warning = 1;
    port_num = 0;
}


QString API::getPortname() const
{
    return serial.getPortname();
}

int API::getBaudrate() const
{
    return serial.getBaudrate();
}

void API::run()
{
    //open and configure serial port
    int success = serial.openPort();
    if (success==1)
    {
        serial.closeSerial();
        return;
    }
    success = serial.configurePort();
    int n;

    while (!isInterruptionRequested())  //(!stopThread)
    {
        success = checkUSB(success);
        if (success) break;


        n = serial.readIncoming(); // read messages from serial port
        process(); // returns number of bytes read

        if (!notification_request_confirmed)
        {
            emit resendNotificationSignal();
        }

        if (!request_queue.empty())
        {
            request_queue.lock();
            for (int i = 0; i < 5; i++)
            {
                serial.writeTxMessageToMCU(request_queue.pop()); // write all outgoing messages to serial port
            }
            request_queue.wake();
        }

        msleep(35);
    }
    serial.closeSerial();
}

int API::checkUSB(int success)
{
    //If the system controller is disconnected and there are only 2 usb devices connected,
    //(Linux Foundation 2.0 root hub and Standard Microsystems Corp. USB 2.0 Hub)
    //then the _signal_warning variable will change to 0
    //This assumes that neither device won't be disconnected and only the system controller will be.
    if (m_currentDevices.deviceCount() < 3 && _signal_warning == 1)
    {
        _signal_warning = 0;
    }
    //If _signal_warning is flipped and the system controller is reconnected,
    //a new serial port will be opened and configured.
    if (m_currentDevices.deviceCount() >= 3 && _signal_warning == 0)
    {
        //closes previous serial port.
        serial.closeSerial();
        //The portname for the system controller will flip between "ttyUSB0" and "ttyUSB1"
        if (port_num == 0)
        {
            port_num = 1;
        }
        else if (port_num == 1)
        {
            port_num = 0;
        }
        myPortName = myPortName.mid(0,11) + QString::number(port_num);

        //Opens and configures serial port with new name.
        serial.setPortname(myPortName);

        success = serial.openPort();
        if (success==1)
        {
            return success;
        }
        _signal_warning = 1;
        success = serial.configurePort();
    }
    return success;
}

/* SERIAL COMMUNICATION PARSERS */


void API::process()
{
    while (serial.nextByteAvailable())
    {
        processBytes(serial.getRxByte());
    }
}

void API::processBytes(unsigned char byte)
{
    if (_in_progress==1)
    {
        if (_op_code==255) // if op-code is undefined //TODO: Should turn this into enum for readability
        {
            _op_code = byte;
            _message_length = getMessageLength(_op_code); //returns 0 if not found
            input_buffer[_ndx]=_op_code;
            _ndx++; // index
        }
        else if (_message_length!=255) //message_length!=0 //when would message length == 255?
        {
            input_buffer[_ndx]=byte;
            _message_length--;
            _ndx++;
            if (_message_length<=0)
            {
                input_buffer[_ndx]='\0';
                if (checkCRC(&input_buffer[0],_ndx)==1)
                {
                    handleRequest(&input_buffer[0]);
                }
                //reset //TODO: maybe make method for readability
                _op_code=255;
                _in_progress=0;
                _ndx=0;
            }
        }
        else // reset
        {
            _op_code=255;
            _in_progress = 0;
            _ndx=0;
        }
    }
    else if (byte==255)
    {
        _in_progress = 1;
    }
        
}

void API::floatToBytes(float src,unsigned char* dst)
{
    union {
        float f;
        unsigned char b[4];
    } floatTranslation;
    floatTranslation.f = src;
    dst[0] = floatTranslation.b[0];
    dst[1] = floatTranslation.b[1];
    dst[2] = floatTranslation.b[2];
    dst[3] = floatTranslation.b[3];
}

float API::bytesToFloat(const unsigned char* src)
{
    union {
        float f;
        unsigned char b[4];
    } floatTranslation;

    floatTranslation.b[0] = *src;
    src++;
    floatTranslation.b[1] = *src;
    src++;
    floatTranslation.b[2] = *src;
    src++;
    floatTranslation.b[3] = *src;
    src++;
    return floatTranslation.f;
}

void API::handleRequest(unsigned char* buffer)
{
    unsigned char op_code = buffer[0];

    switch(op_code)
    {
        case (int)rxOpCodes::SYSTEM_POWER_ON_SEND:
            handlePowerCycle();
            break;
        case (int)rxOpCodes::SYSTEM_GET_SETTINGS_RESPONSE:
            handleGetSettingsResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_NOTIFICATIONS_RESPONSE:
            handleEnabledNotifications();
            break;
        case (int)rxOpCodes::SYSTEM_GET_OP_MODES_RESPONSE:
            handleGetModesResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_GET_SUBSYSTEM_STATE_RESPONSE:
            handleGetSubsystemStates(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_GET_SYSTEM_VERSION_RESPONSE:
            handleSystemVersionResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_SET_SETTINGS_RESPONSE:
            handleSetResponse();
            break;
        case (int)rxOpCodes::SYSTEM_GET_MEASURED_RESPONSE:
            handleGetSensorMeasurementResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_CLEAR_WARNING_RESPONSE:
            handleClearWarning(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_OP_MODE_RESPONSE:
            handleModeResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_OP_MODE_REQUEST:
            handleModeRequest(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_NOTIFICATION_UPDATE:
            handleNotification(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_SUBSYSTEM_STATUS_UPDATE:
            handleSubsystemStateChange(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_VENTILATION_STATUS_UPDATE:
            handleVentilationStatusUpdate(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_HMI_BUTTON_PUSHED_UPDATE:
            handleHMIButtonPush(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_SHUTDOWN_REQUEST:
            handleInitPowerdown();
            break;
        case (int)rxOpCodes::SYSTEM_SHUTDOWN_CONFIRM_RECEIVED:
            handleInitPowerdownCommandOK(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_SET_DPR_CAL_VAL_RESPONSE:
            handleDPRValSetResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_PRESSURE_SENSOR_ZERO_RESPONSE:
            handleSensorZeroResponse(buffer);
            break;
        case (int)rxOpCodes::SYSTEM_SERVICE_NOTIFICATION_UPDATE:
            handleServiceNotifications(buffer);
            break;
        default:
            break;
    }
}

int API::getMessageLength(unsigned char op_code)    
{           
    switch(op_code)
    {
        case (int)rxOpCodes::SYSTEM_POWER_ON_SEND:
            return (int) rxLengths::SYSTEM_POWER_ON_SEND;
            break;
        case (int)rxOpCodes::SYSTEM_GET_SETTINGS_RESPONSE:
            return (int) rxLengths::SYSTEM_GET_SETTINGS_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_NOTIFICATIONS_RESPONSE:
            return (int) rxLengths::SYSTEM_ENABLE_NOTIFICATIONS_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_GET_OP_MODES_RESPONSE:
            return (int) rxLengths::SYSTEM_GET_OP_MODES_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_GET_SUBSYSTEM_STATE_RESPONSE:
            return (int) rxLengths::SYSTEM_GET_SUBSYSTEM_STATE_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_GET_SYSTEM_VERSION_RESPONSE:
            return (int) rxLengths::SYSTEM_GET_SYSTEM_VERSION_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_SET_SETTINGS_RESPONSE:
            return (int) rxLengths::SYSTEM_SET_SETTINGS_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_GET_MEASURED_RESPONSE:
            return (int) rxLengths::SYSTEM_GET_MEASURED_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_CLEAR_WARNING_RESPONSE:
            return (int) rxLengths::SYSTEM_CLEAR_WARNING_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_OP_MODE_RESPONSE:
            return (int) rxLengths::SYSTEM_ENABLE_OP_MODE_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_OP_MODE_REQUEST:
            return (int) rxLengths::SYSTEM_ENABLE_OP_MODE_REQUEST;
            break;
        case (int)rxOpCodes::SYSTEM_NOTIFICATION_UPDATE:
            return (int) rxLengths::SYSTEM_NOTIFICATION_UPDATE;
            break;
        case (int)rxOpCodes::SYSTEM_SUBSYSTEM_STATUS_UPDATE:
            return (int) rxLengths::SYSTEM_SUBSYSTEM_STATUS_UPDATE;
            break;
        case (int)rxOpCodes::SYSTEM_VENTILATION_STATUS_UPDATE:
            return (int) rxLengths::SYSTEM_VENTILATION_STATUS_UPDATE;
            break;
        case (int)rxOpCodes::SYSTEM_HMI_BUTTON_PUSHED_UPDATE:
            return (int) rxLengths::SYSTEM_HMI_BUTTON_PUSHED_UPDATE;
            break;
        case (int)rxOpCodes::SYSTEM_SHUTDOWN_REQUEST:
            return (int) rxLengths::SYSTEM_SHUTDOWN_REQUEST;
            break;
        case (int)rxOpCodes::SYSTEM_SHUTDOWN_CONFIRM_RECEIVED:
            return (int) rxLengths::SYSTEM_SHUTDOWN_CONFIRM_RECEIVED;
            break;
        case (int)rxOpCodes::SYSTEM_SET_DPR_CAL_VAL_RESPONSE:
            return (int) rxLengths::SYSTEM_SET_DPR_CAL_VAL_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_ENABLE_PRESSURE_SENSOR_ZERO_RESPONSE:
            return (int) rxLengths::SYSTEM_ENABLE_PRESSURE_SENSOR_ZERO_RESPONSE;
            break;
        case (int)rxOpCodes::SYSTEM_SERVICE_NOTIFICATION_UPDATE:
            return (int) rxLengths::SYSTEM_SERVICE_NOTIFICATION_UPDATE;
            break;
        default:
            return 0;
            break;
    }
}

void API::sendComm(unsigned char* buffer, int n)
{
    unsigned char crc = calculateCRC(buffer,n);

    request_queue.push(Message(buffer, crc, n));
}

void API::sendComm1(unsigned char * buffer, int n)
{
    unsigned char crc = calculateCRC(buffer,n);

    request_queue.push(Message(buffer, crc, n));
}

unsigned char API::calculateCRC(unsigned char* buffer, int n)
{
    const int generator = 341;
    unsigned char crc=0;
    for (int i=0;i<n;i++)
    {
        crc ^= *buffer;
        buffer++;
        for (int j = 0;j<8;j++)
        {
            if ((crc&0x80)!=0)
            {
                crc = (unsigned char) ((crc<<1) ^ generator);
            }
            else
            {
                crc = crc<<1;
            }
        }
    }
    return crc;
}

int API::checkCRC(unsigned char* buffer, int n)
{
    unsigned char crc = calculateCRC(buffer,n);
    if (crc!=0)
    {
        return 0;
    }
    return 1;
}

/*POWER CYCLE PATHWAY*/

void API::queuePowerCycleResponse()
{
    unsigned char power_cycle_response[(int)txLengths::DISPLAY_POWER_ON_RECEIVED];
    power_cycle_response[0]=(unsigned char)txOpCodes::DISPLAY_POWER_ON_RECEIVED;
    unsigned char crc = calculateCRC(&power_cycle_response[0],(int)txLengths::DISPLAY_POWER_ON_RECEIVED);

    request_queue.push(Message(power_cycle_response,crc, (int)txLengths::DISPLAY_POWER_ON_RECEIVED));
}

void API::handlePowerCycle()
{
    queuePowerCycleResponse();
}

/*GET SETTINGS PATHWAY*/

void API::sendGetSettingsSlot()
{
    queueGetSettingsRequest();
}

void API::queueGetSettingsRequest()
{
    unsigned char get_settings_request[(int)txLengths::DISPLAY_GET_SETTINGS_REQUEST];
    get_settings_request[0]=(int)txOpCodes::DISPLAY_GET_SETTINGS_REQUEST;

    unsigned char crc = calculateCRC(get_settings_request,(int)txLengths::DISPLAY_GET_SETTINGS_REQUEST);

    request_queue.push(Message(get_settings_request,crc,(int)txLengths::DISPLAY_GET_SETTINGS_REQUEST));
}

void API::handleGetSettingsResponse(unsigned char* buffer)
{
    if (!get_settings_confirmed)
    {
        get_settings_confirmed=1;
    }

    buffer++;
    QVector<int> settings_data(QVector<int>(NUM_SETTINGS));
    int *data = settings_data.data();
    for (int i=0;i<NUM_SETTINGS;i++,buffer+=4)
    {
        data[i] = bytesToFloat(buffer);
    }
    emit updateSettingsSignal(settings_data);
}

/*ENABLE NOTIFICATION PATHWAY*/

void API::sendNotificationSlot(int enable_disable)
{
    queueNotificationRequest(enable_disable);
    notification_request_confirmed = 0;
    /* write notifications request */
}

void API::resendNotificationSlot(int enable_disable)
{
    queueNotificationRequest(enable_disable);
}

void API::queueNotificationRequest(unsigned char enable_disable)
{
    unsigned char notification_request[(int)txLengths::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST];
    notification_request[0]=(int)txOpCodes::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST;
    notification_request[1]=enable_disable;

    unsigned char crc = calculateCRC(notification_request,(int)txLengths::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST);

    request_queue.push(Message(notification_request,crc,(int)txLengths::DISPLAY_ENABLE_NOTIFICATIONS_REQUEST));
}

void API::handleEnabledNotifications()
{
    if (!notification_request_confirmed)
    {
        notification_request_confirmed=1;
    }
    emit enableNotificationSignal();
}

/*GET OP MODES PATHWAY*/

void API::getModesSlot()
{
    unsigned char request[(int)txLengths::DISPLAY_GET_OP_MODES_REQUEST];
    request[0] = (unsigned char) txOpCodes::DISPLAY_GET_OP_MODES_REQUEST;

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_GET_OP_MODES_REQUEST);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_GET_OP_MODES_REQUEST));
}

void API::handleGetModesResponse(unsigned char* buffer)
{
    buffer ++;
    QVector<int> modes;
    for (int i = 0; i < NUM_MODES; i++)
    {
        modes.append(*buffer);
        buffer++;
    }
    emit sendModesSignal(modes);
}

/*GET SUBSYSTEM STATUS PATHWAY*/

void API::getSubsystemStates()
{
    unsigned char request[(int)txLengths::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST];
    request[0] = (unsigned char) txOpCodes::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST;

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_GET_SUBSYSTEM_STATE_REQUEST));
}

void API::handleGetSubsystemStates(unsigned char *buffer)
{
    buffer++;
    QVector<unsigned char> result(QVector<unsigned char>(NUM_SUBSYSTEMS));

    unsigned char *data = result.data();
    for (int i=0;i<result.size();i++,buffer++)
    {
        data[i] = *buffer;
    }
    emit subsystemStatesChangeReceived(result);
}

/* SYSTEM VERSION PATHWAY */

void API::handleSystemVersionResponse(unsigned char* buffer)
{
    unsigned char major = *(++buffer);
    unsigned char minor = *(++buffer);
    unsigned char patch = *(++buffer);
    emit systemVersion(major,minor,patch);
}

void API::queryVersion()
{
    unsigned char message [(int)txLengths::DISPLAY_GET_SYSTEM_VERSION_REQUEST];
    message[0] = (unsigned char)txOpCodes::DISPLAY_GET_SYSTEM_VERSION_REQUEST;

    unsigned char crc = calculateCRC(message,(int)txLengths::DISPLAY_GET_SYSTEM_VERSION_REQUEST);

    request_queue.push(Message(message,crc,(int)txLengths::DISPLAY_GET_SYSTEM_VERSION_REQUEST));
}

/*SET SETTINGS PATHWAY*/

void API::sendSettingsSlot(QVector<int> settings)
{
    setSettings(settings);
    settings_set=0;
}

void API::handleSetResponse()
{
    emit settingsConfirmed();
}

void API::setSettings(QVector<int> settings)
{
    unsigned char set_request[(int)txLengths::DISPLAY_SET_SETTINGS_REQUEST];
    set_request[0] = (int)txOpCodes::DISPLAY_SET_SETTINGS_REQUEST;
    int index = 1;

    if(settings.length() == NUM_SETTINGS)
    {
        for(int i = 0; i< NUM_SETTINGS; i++)
        {
            //Setting value for HIGH DPR Calibration
            if (i == 0 && temp_dp_value_flag)
            {
                floatToBytes(temp_dp_value, &set_request[index]);
            }
            else
            {
                floatToBytes(settings[i],&set_request[index]);
            }
            index = index + 4;
        }
    }

    unsigned char crc = calculateCRC(set_request,(int)txLengths::DISPLAY_SET_SETTINGS_REQUEST);

    request_queue.push(Message(set_request,crc,(int)txLengths::DISPLAY_SET_SETTINGS_REQUEST));
}

/* GET MEASURED PATHWAY*/

void API::getMeasured(unsigned char id)
{
    unsigned char request[(int)txLengths::DISPLAY_GET_MEASURED_REQUEST];
    request[0] = (unsigned char)txOpCodes::DISPLAY_GET_MEASURED_REQUEST;
    request[1] = id;
    sendComm(&request[0], (int)txLengths::DISPLAY_GET_MEASURED_REQUEST);
}

void API::handleGetSensorMeasurementResponse(unsigned char *buffer)
{
    buffer ++;
    unsigned char id = *buffer;
    buffer ++;

    if (id == 17)
    {
        unsigned char value = bytesToFloat(buffer);
        emit receiveWaterSensorValue(id,value);
        return;
    }

    if (id == 32 || id == 33)
    {
        emit receiveVoltValue(id,bytesToFloat(buffer));
        return;
    }

    unsigned char value = bytesToFloat(buffer);
    emit receiveMeasuredValue(id, value);
}

/*CLEAR WARNING PATHWAY*/

void API::handleClearWarning(unsigned char* buffer)
{
    buffer++;
    int warning_id = buffer[0];
    emit clearWarningSignal(warning_id);
}

void API::clearWarningSlot(int warning_id)
{
    unsigned char clear_warning_request[(int)txLengths::DISPLAY_CLEAR_WARNING_REQUEST];
    clear_warning_request[0]=(int)txOpCodes::DISPLAY_CLEAR_WARNING_REQUEST;
    clear_warning_request[1]=warning_id;

    unsigned char crc = calculateCRC(clear_warning_request,(int)txLengths::DISPLAY_CLEAR_WARNING_REQUEST);

    request_queue.push(Message(clear_warning_request,crc,(int)txLengths::DISPLAY_CLEAR_WARNING_REQUEST));
}

/*DISPLAY OP MODE REQUEST PATHWAY*/

void API::handleModeResponse(unsigned char* buffer)
{
    buffer ++;
    unsigned char modeID= *buffer;
    buffer ++;
    unsigned char enabled = *buffer;

    emit modeSetSignal(modeID, enabled);
}

void API::sendModeSlot(unsigned char id, unsigned char enable)
{
    unsigned char request[(int)txLengths::DISPLAY_ENABLE_OP_MODE_REQUEST];
    request[0]=(unsigned char)txOpCodes::DISPLAY_ENABLE_OP_MODE_REQUEST;
    request[1]=id;
    request[2]=enable;
    request[3]=1;

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_ENABLE_OP_MODE_REQUEST);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_ENABLE_OP_MODE_REQUEST));
}

/*DISPLAY OP MODE RESPONSE PATHWAY*/

void API::handleModeRequest(unsigned char* buffer)
{
    buffer ++;
    unsigned char modeID= *buffer;
    buffer ++;
    unsigned char enabled = *buffer;
    buffer ++;
    unsigned char success = *buffer;

    queueModeResponse(modeID, enabled);

    emit setModeSignal(modeID, enabled, success);
}

void API::queueModeResponse(unsigned char modeID, unsigned char value)
{
    unsigned char message [(int)txLengths::DISPLAY_ENABLE_OP_MODE_RESPONSE];
    message[0] = (unsigned char)txOpCodes::DISPLAY_ENABLE_OP_MODE_RESPONSE;
    message[1] = modeID;
    message[2] = value;

    unsigned char crc = calculateCRC(message,(int)txLengths::DISPLAY_ENABLE_OP_MODE_RESPONSE);

    request_queue.push(Message(message,crc,(int)txLengths::DISPLAY_ENABLE_OP_MODE_RESPONSE));
}

/*NOTIFICATION PATHWAY*/

void API::handleNotification(unsigned char* buffer)
{
    if (!notification_request_confirmed)
    {
        notification_request_confirmed=1;
    }

    if (m_num_of_notifications % 10 == 0)
    {
        queueNotificationResponse();
    }

    if (m_num_of_notifications > 60)
    {
        emit resendMessagesSignal();
        m_num_of_notifications = -1;
    }
    m_num_of_notifications++;

    buffer++;

    QVector<float> notification(QVector<float>(NUM_SETTINGS_NOTIFICATIONS+NUM_CALCULATIONS_NOTIFICATIONS + 1));

    float *data = notification.data();
    for (int i=0;i<NUM_SETTINGS_NOTIFICATIONS+NUM_CALCULATIONS_NOTIFICATIONS;i++,buffer+=4)
    {
        data[i] = bytesToFloat(buffer);
    }

    handleWarnings(buffer);
    buffer += NUM_WARNINGS_BYTES;
    notification[NUM_SETTINGS_NOTIFICATIONS+NUM_CALCULATIONS_NOTIFICATIONS] = *buffer;

    emit notificationUpdateSignal(notification);
}

void API::handleWarnings(unsigned char* buffer)
{
    QVector<unsigned char> warnings(QVector<unsigned char>(NUM_WARNINGS));
    unsigned char *warnings_data = warnings.data();

    int bitIndex = 0;

    for (int k = 0; k < NUM_WARNINGS; k++)
    {
        warnings_data[k] = (buffer[bitIndex / 8] >> (bitIndex % 8)) & 1;
        bitIndex++;
    }
    emit warningUpdateSignal(warnings);
}

void API::queueNotificationResponse()
{
    if (service_flag) return;

    unsigned char notification_response[(int)txLengths::DISPLAY_NOTIFICATION_RECEIVED];
    notification_response[0] = (int)txOpCodes::DISPLAY_NOTIFICATION_RECEIVED;

    unsigned char crc = calculateCRC(notification_response,(int)txLengths::DISPLAY_NOTIFICATION_RECEIVED);

    request_queue.push(Message(notification_response,crc,(int)txLengths::DISPLAY_NOTIFICATION_RECEIVED));
}

/*SUBSYSTEM STATES PATHWAY*/

void API::handleSubsystemStateChange(unsigned char *buffer)
{
    queueSubsystemStateChangedResponse();
    handleGetSubsystemStates(buffer);
}

void API::queueSubsystemStateChangedResponse()
{
    if (service_flag) return;

    unsigned char response[(int)txLengths::DISPLAY_SUBSYSTEM_STATUS_RECEIVED];
    response[0] = (unsigned char) txOpCodes::DISPLAY_SUBSYSTEM_STATUS_RECEIVED;

    unsigned char crc = calculateCRC(response,(int)txLengths::DISPLAY_SUBSYSTEM_STATUS_RECEIVED);

    request_queue.push(Message(response,crc,(int)txLengths::DISPLAY_SUBSYSTEM_STATUS_RECEIVED));
}

/*VENTILATION PATHWAY*/

void API::handleVentilationStatusUpdate(unsigned char *buffer)
{
    queueVentilationStatusResponse();
    emit ventilationStateChangeReceived(*++buffer);
}

void API::queueVentilationStatusResponse()
{
    unsigned char response[(int)txLengths::DISPLAY_VENTILATION_STATUS_RECEIVED];
    response[0] = (unsigned char) txOpCodes::DISPLAY_VENTILATION_STATUS_RECEIVED;
    sendComm1(&response[0], (int)txLengths::DISPLAY_VENTILATION_STATUS_RECEIVED);
}

/*HMI BUTTON PUSH PATHWAY*/

void API::handleHMIButtonPush(unsigned char *buffer)
{
    ++buffer;
    queueHMIButtonPushResponse(*buffer);
    emit HMIButtonPushReceived(*buffer);
}

void API::queueHMIButtonPushResponse(unsigned char id)
{
    unsigned char response[(int)txLengths::DISPLAY_HMI_BUTTON_PUSHED_RECEIVED];
    response[0] = (unsigned char) txOpCodes::DISPLAY_HMI_BUTTON_PUSHED_RECEIVED;
    response[1] = id;
    sendComm1(&response[0], (int)txLengths::DISPLAY_HMI_BUTTON_PUSHED_RECEIVED);
}

/*SHUTDOWN PATHWAY*/

void API::queueInitPowerdownOk()
{
    unsigned char request[(int)txLengths::DISPLAY_SHUTDOWN_RECEIVED];
    request[0] = (unsigned char) txOpCodes::DISPLAY_SHUTDOWN_RECEIVED;

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_SHUTDOWN_RECEIVED);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_SHUTDOWN_RECEIVED));
}

void API::handleInitPowerdown()
{
    emit initPowerdown();
    queueInitPowerdownOk();
}

/*SHUTDOWN CONFIRM PATHWAY*/

void API::confirmPowerdown(unsigned char powerdown)
{
    unsigned char request[(int)txLengths::DISPLAY_SHUTDOWN_CONFIRM_SEND];
    request[0] = (unsigned char) txOpCodes::DISPLAY_SHUTDOWN_CONFIRM_SEND;
    request[1] = powerdown;

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_SHUTDOWN_CONFIRM_SEND);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_SHUTDOWN_CONFIRM_SEND));

}

void API::handleInitPowerdownCommandOK(unsigned char* buffer)
{
    buffer++;
    emit powerdownConfirmed(*buffer);
}

/*DRIVING PRESSURE REGULATOR SET CAL VAL*/

void API::slotDPR(unsigned char enable_disabled)
{
    dpr_flag = enable_disabled;
}

void API::handleDPRValSetResponse(unsigned char *buffer)
{
    //qDebug() << "DPR VAL SET";
    emit signalDPRValue();
}

void API::slotDPRValue(unsigned char value) //, unsigned char regAirValue, unsigned char regO2Value, float setValue)
{
    //qDebug() << "SET DPR VAL " + QString::number(value);
    unsigned char request[(int)txLengths::DISPLAY_SET_DPR_CAL_VAL_REQUEST];
    request[0] = (unsigned char) txOpCodes::DISPLAY_SET_DPR_CAL_VAL_REQUEST;
    request[1] = value;

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_SET_DPR_CAL_VAL_REQUEST);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_SET_DPR_CAL_VAL_REQUEST));
}

void API::slotTempDP(unsigned char flag, float value)
{
    temp_dp_value_flag = flag;
    temp_dp_value = value;
}

void API::slotCalibrationMessages(unsigned char value)
{
    service_flag = value;
}

/* ZERO PRESSURE SENSOR PATHWAY */

void API::handleSensorZeroResponse(unsigned char *buffer)
{
    buffer++;
    QVector<unsigned char> response = QVector<unsigned char>(2);
    response[0] = *buffer;
    buffer++;
    response[1] = *buffer;
    emit sensorZeroed(response);
}

void API::zeroSensor(QVector<float> values)
{
    unsigned char request[(int)txLengths::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST];
    request[0] = (unsigned char) txOpCodes::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST;
    request[1] = (unsigned char) values[0];


    floatToBytes(values[1], &request[2]);

    unsigned char crc = calculateCRC(request,(int)txLengths::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST);

    request_queue.push(Message(request,crc,(int)txLengths::DISPLAY_ENABLE_PRESSURE_SENSOR_ZERO_REQUEST));
}

/* SERVICE NOTIFICATION PATHWAY */

void API::handleServiceNotifications(unsigned char *buffer)
{

    if (m_num_of_notifications > 60)
    {
        emit resendMessagesSignal();
        m_num_of_notifications = -1;
    }
    m_num_of_notifications++;

    buffer++;

    QVector<float> notification(QVector<float>(NUM_SERVICE_NOTIFICATIONS));

    float *data = notification.data();
    for (int i = 0; i < NUM_SERVICE_NOTIFICATIONS; i++, buffer+=4)
    {
        data[i] = bytesToFloat(buffer);
        //qDebug() << "Service ID: " + QString::number(i) + ", value: " + QString::number(data[i]);
    }

    emit serviceNotificationUpdateSignal(notification);
}
