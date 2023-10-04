/**
 * @author Joseph Aversa
 * @name contact_manager
 * @date 02/01/2023
 *
 * Program allows technician to update the contact information for the service company and the company that sells the Nvent-Vita.
 * Values are saved on .csv files.
 */

#include "contact_manager.h"

ContactManager::ContactManager(QObject *parent) :
    QObject(parent)
{
    std::vector<std::string> tColumns = {"TYPE", "INFO"};

    m_serviceCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(SERVICE_CONTACT_FILE), &tColumns[0], 2);
    updateServiceContact();

    m_salesCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(SALES_CONTACT_FILE), &tColumns[0], 2);
    updateSalesContact();
}

void ContactManager::updateServiceContact()
{
    if (m_serviceCsvManager.getNumEntries() != 7)
    {
        setService("Susquehanna Micro Inc.","198 West Beaver Street","Hallam","PA","17406","susquemicro.com","(888)730-5463");
        return;
    }

    std::vector<std::string> vector1 = m_serviceCsvManager.readRecord(0);
    std::vector<std::string> vector2 = m_serviceCsvManager.readRecord(1);
    std::vector<std::string> vector3 = m_serviceCsvManager.readRecord(2);
    std::vector<std::string> vector4 = m_serviceCsvManager.readRecord(3);
    std::vector<std::string> vector5 = m_serviceCsvManager.readRecord(4);
    std::vector<std::string> vector6 = m_serviceCsvManager.readRecord(5);
    std::vector<std::string> vector7 = m_serviceCsvManager.readRecord(6);

    //Reboots information if .csv is corrupted
    if (vector1.size() < 2)
    {
        vector1 = {COMPANY,"TBD"};
    }
    if (vector2.size() < 2)
    {
        vector2 = {STREET,"TBD"};
    }
    if (vector3.size() < 2)
    {
        vector3 = {CITY,"TBD"};
    }
    if (vector4.size() != 2)
    {
        vector4 = {STATE,"**"};
    }
    else if (vector4.at(1).length() != 2)
    {
        vector4 = {STATE,"**"};
    }
    if (vector5.size() != 2)
    {
        vector5 = {POSTAL_CODE,"*****"};
    }
    else if (vector5.at(1).length() != 5)
    {
        vector5 = {POSTAL_CODE,"*****"};
    }
    if (vector6.size() < 2)
    {
        vector6 = {EMAIL,"TBD"};
    }
    if (vector7.size() != 2)
    {
        vector7 = {PHONE_NUMBER,"(***)***-****"};
    }
    else if (vector7.at(1).length() != 13)
    {
        vector7 = {PHONE_NUMBER,"(***)***-****"};
    }

    m_service_company_name = getFullString(vector1);
    m_service_street = getFullString(vector2);
    m_service_city = getFullString(vector3);
    m_service_state = QString::fromStdString(vector4.at(1));
    m_service_postal_code = QString::fromStdString(vector5.at(1));
    m_service_email = getFullString(vector6);
    m_service_phone_number = QString::fromStdString(vector7.at(1));

    emit contactChanged();
}

void ContactManager::updateSalesContact()
{
    if (m_salesCsvManager.getNumEntries() != 7)
    {
        setSales("Lantern Medical, LLC","21525 Ridgetop Circle, Suite 180","Sterling","VA","20166","info@lantern-medical.com","(571)308-2773");
        return;
    }

    std::vector<std::string> vector1 = m_salesCsvManager.readRecord(0);
    std::vector<std::string> vector2 = m_salesCsvManager.readRecord(1);
    std::vector<std::string> vector3 = m_salesCsvManager.readRecord(2);
    std::vector<std::string> vector4 = m_salesCsvManager.readRecord(3);
    std::vector<std::string> vector5 = m_salesCsvManager.readRecord(4);
    std::vector<std::string> vector6 = m_salesCsvManager.readRecord(5);
    std::vector<std::string> vector7 = m_salesCsvManager.readRecord(6);

    //Reboots information if .csv is corrupted
    if (vector1.size() < 2)
    {
        vector1 = {COMPANY,"TBD"};
    }
    if (vector2.size() < 2)
    {
        vector2 = {STREET,"TBD"};
    }
    if (vector3.size() < 2)
    {
        vector3 = {CITY,"TBD"};
    }
    if (vector4.size() != 2)
    {
        vector4 = {STATE,"**"};
    }
    else if (vector4.at(1).length() != 2)
    {
        vector4 = {STATE,"**"};
    }
    if (vector5.size() != 2)
    {
        vector5 = {POSTAL_CODE,"*****"};
    }
    else if (vector5.at(1).length() != 5)
    {
        vector5 = {POSTAL_CODE,"*****"};
    }
    if (vector6.size() < 2)
    {
        vector6 = {EMAIL,"TBD"};
    }
    if (vector7.size() != 2)
    {
        vector7 = {PHONE_NUMBER,"(***)***-****"};
    }
    else if (vector7.at(1).length() != 13)
    {
        vector7 = {PHONE_NUMBER,"(***)***-****"};
    }

    m_sales_company_name = getFullString(vector1);
    m_sales_street = getFullString(vector2);
    m_sales_city = getFullString(vector3);
    m_sales_state = QString::fromStdString(vector4.at(1));
    m_sales_postal_code = QString::fromStdString(vector5.at(1));
    m_sales_email = getFullString(vector6);
    m_sales_phone_number = QString::fromStdString(vector7.at(1));

    emit contactChanged();
}

QString ContactManager::getFullString(std::vector<std::string> vector)
{
    QString temp = "";
    for (int i = 1; i < vector.size(); i++)
    {
        temp = temp  + QString::fromStdString(vector.at(i));
        if (i < vector.size() - 1)
        {
            temp = temp + ",";
        }
    }
    return temp;
}

QString ContactManager::getServiceCompanyName()
{
    return m_service_company_name;
}

QString ContactManager::getServiceStreet()
{
    return m_service_street;
}

QString ContactManager::getServiceCity()
{
    return m_service_city;
}

QString ContactManager::getServiceState()
{
    return m_service_state;
}

QString ContactManager::getServicePostalCode()
{
    return m_service_postal_code;
}

QString ContactManager::getServiceEmail()
{
    return m_service_email;
}

QString ContactManager::getServicePhoneNumber()
{
    return m_service_phone_number;
}

QString ContactManager::getSalesCompanyName()
{
    return m_sales_company_name;
}

QString ContactManager::getSalesStreet()
{
    return m_sales_street;
}

QString ContactManager::getSalesCity()
{
    return m_sales_city;
}

QString ContactManager::getSalesState()
{
    return m_sales_state;
}

QString ContactManager::getSalesPostalCode()
{
    return m_sales_postal_code;
}

QString ContactManager::getSalesEmail()
{
    return m_sales_email;
}

QString ContactManager::getSalesPhoneNumber()
{
    return m_sales_phone_number;
}

void ContactManager::setService(QString name, QString street, QString city, QString state, QString postalCode, QString email, QString phoneNumber)
{
    if (m_serviceCsvManager.getNumEntries() > 0)
    {
        for (int i = 0; i < 7; i++)
        {
            m_serviceCsvManager.deleteRecord(0);
        }
    }

    m_service_company_name = name;
    m_service_street = street;
    m_service_city = city;
    m_service_state = state;
    m_service_postal_code = postalCode;
    m_service_email = email;
    m_service_phone_number = phoneNumber;

    std::vector<std::string> vector1 = {COMPANY,m_service_company_name.toStdString()};
    std::vector<std::string> vector2 = {STREET,m_service_street.toStdString()};
    std::vector<std::string> vector3 = {CITY,m_service_city.toStdString()};
    std::vector<std::string> vector4 = {STATE,m_service_state.toStdString()};
    std::vector<std::string> vector5 = {POSTAL_CODE,m_service_postal_code.toStdString()};
    std::vector<std::string> vector6 = {EMAIL,m_service_email.toStdString()};
    std::vector<std::string> vector7 = {PHONE_NUMBER,m_service_phone_number.toStdString()};

    m_serviceCsvManager.createRecord(&vector1[0]);
    m_serviceCsvManager.createRecord(&vector2[0]);
    m_serviceCsvManager.createRecord(&vector3[0]);
    m_serviceCsvManager.createRecord(&vector4[0]);
    m_serviceCsvManager.createRecord(&vector5[0]);
    m_serviceCsvManager.createRecord(&vector6[0]);
    m_serviceCsvManager.createRecord(&vector7[0]);
    emit contactChanged();

    qInfo() << "NVENT" << "," << "CONTACTS" << "," << "Service Contact Information: " + m_service_company_name.replace(",", ";") + "; " + m_service_street.replace(",", ";") + "; " + m_service_city.replace(",", ";") + "; " + m_service_state + "; " + m_service_postal_code + "; " + m_service_email.replace(",", ";") + "; " + m_service_phone_number + ".";
}

void ContactManager::setSales(QString name, QString street, QString city, QString state, QString postalCode, QString email, QString phoneNumber)
{
    if (m_salesCsvManager.getNumEntries() > 0)
    {
        for (int i = 0; i < 7; i++)
        {
            m_salesCsvManager.deleteRecord(0);
        }
    }

    m_sales_company_name = name;
    m_sales_street = street;
    m_sales_city = city;
    m_sales_state = state;
    m_sales_postal_code = postalCode;
    m_sales_email = email;
    m_sales_phone_number = phoneNumber;

    std::vector<std::string> vector1 = {COMPANY,m_sales_company_name.toStdString()};
    std::vector<std::string> vector2 = {STREET,m_sales_street.toStdString()};
    std::vector<std::string> vector3 = {CITY,m_sales_city.toStdString()};
    std::vector<std::string> vector4 = {STATE,m_sales_state.toStdString()};
    std::vector<std::string> vector5 = {POSTAL_CODE,m_sales_postal_code.toStdString()};
    std::vector<std::string> vector6 = {EMAIL,m_sales_email.toStdString()};
    std::vector<std::string> vector7 = {PHONE_NUMBER,m_sales_phone_number.toStdString()};

    m_salesCsvManager.createRecord(&vector1[0]);
    m_salesCsvManager.createRecord(&vector2[0]);
    m_salesCsvManager.createRecord(&vector3[0]);
    m_salesCsvManager.createRecord(&vector4[0]);
    m_salesCsvManager.createRecord(&vector5[0]);
    m_salesCsvManager.createRecord(&vector6[0]);
    m_salesCsvManager.createRecord(&vector7[0]);

    emit contactChanged();

    qInfo() << "NVENT" << "," << "CONTACTS" << "," << "Sales Contact Information: " + m_sales_company_name.replace(",", ";") + "; " + m_sales_street.replace(",", ";") + "; " + m_sales_city.replace(",", ";") + "; " + m_sales_state + "; " + m_sales_postal_code + "; " + m_sales_email.replace(",", ";") + "; " + m_sales_phone_number + ".";
}


