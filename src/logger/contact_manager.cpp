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

    m_serviceCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(SERVICE_CONTACT_FILE), tColumns.data(), 2);
    updateServiceContact();

    m_salesCsvManager = CSVManager("/media/NVENT_FILES/" + std::string(SALES_CONTACT_FILE), tColumns.data(), 2);
    updateSalesContact();
}

QString ContactManager::getFullString(std::vector<std::string> vector)
{
    QString temp = QString::fromStdString("");
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

void ContactManager::updateServiceContact()
{
    if (m_serviceCsvManager.getNumEntries() != number_of_entries)
    {
        setService(
                    QString::fromStdString("Susquehanna Micro Inc."),
                    QString::fromStdString("198 West Beaver Street"),
                    QString::fromStdString("Hallam"),
                    QString::fromStdString("PA"),
                    QString::fromStdString("17406"),
                    QString::fromStdString("susquemicro.com"),
                    QString::fromStdString("(888)730-5463")
                    );
        return;
    }

    m_service_company_name = getFullString(constructServiceCompanyName());
    m_service_street = getFullString(constructServiceStreet());
    m_service_city = getFullString(constructServiceCity());
    m_service_state = QString::fromStdString(constructServiceState().at(1));
    m_service_postal_code = QString::fromStdString(constructServicePostalCode().at(1));
    m_service_email = getFullString(constructServiceEmail());
    m_service_phone_number = QString::fromStdString(constructServicePhoneNumber().at(1));

    emit contactChanged();
}

void ContactManager::setService(
        const QString &name,
        const QString &street,
        const QString &city,
        const QString &state,
        const QString &postalCode,
        const QString &email,
        const QString &phoneNumber
        )
{
    if (m_serviceCsvManager.getNumEntries() > 0)
    {
        for (int i = 0; i < number_of_entries; i++)
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

    m_serviceCsvManager.createRecord(vector1.data());
    m_serviceCsvManager.createRecord(vector2.data());
    m_serviceCsvManager.createRecord(vector3.data());
    m_serviceCsvManager.createRecord(vector4.data());
    m_serviceCsvManager.createRecord(vector5.data());
    m_serviceCsvManager.createRecord(vector6.data());
    m_serviceCsvManager.createRecord(vector7.data());
    emit contactChanged();

    qInfo() << "NVENT"
            << ","
            << "CONTACTS"
            << ","
            << "Service Contact Information: " +
               m_service_company_name.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_service_street.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_service_city.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_service_state +
               "; " +
               m_service_postal_code +
               "; " +
               m_service_email.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_service_phone_number +
               ".";
}

std::vector<std::string> ContactManager::constructServiceCompanyName()
{
    const int cvs_index = 0;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {COMPANY,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructServiceStreet()
{
    const int cvs_index = 1;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {STREET,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructServiceCity()
{
    const int cvs_index = 2;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {CITY,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructServiceState()
{
    const int cvs_index = 3;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() != 2 || vector.at(1).length() != 2)
    {
        vector = {STATE,"**"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructServicePostalCode()
{
    const int cvs_index = 4;
    const int postal_code_length = 5;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() != 2 || vector.at(1).length() != postal_code_length)
    {
        vector = {POSTAL_CODE,"*****"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructServiceEmail()
{
    const int cvs_index = 5;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {EMAIL,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructServicePhoneNumber()
{
    const int cvs_index = 6;
    const int phone_number_length = 13;
    std::vector<std::string> vector = m_serviceCsvManager.readRecord(cvs_index);

    if (vector.size() != 2 || vector.at(1).length() != phone_number_length)
    {
        vector = {PHONE_NUMBER,"(***)***-****"};
    }

    return vector;
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

void ContactManager::updateSalesContact()
{
    if (m_salesCsvManager.getNumEntries() != number_of_entries)
    {
        setSales(
                    QString::fromStdString("Lantern Medical, LLC"),
                    QString::fromStdString("21525 Ridgetop Circle, Suite 180"),
                    QString::fromStdString("Sterling"),
                    QString::fromStdString("VA"),
                    QString::fromStdString("20166"),
                    QString::fromStdString("info@lantern-medical.com"),
                    QString::fromStdString("(571)308-2773")
                    );
        return;
    }

    m_sales_company_name = getFullString(constructSalesCompanyName());
    m_sales_street = getFullString(constructSalesStreet());
    m_sales_city = getFullString(constructSalesCity());
    m_sales_state = QString::fromStdString(constructSalesState().at(1));
    m_sales_postal_code = QString::fromStdString(constructSalesPostalCode().at(1));
    m_sales_email = getFullString(constructSalesEmail());
    m_sales_phone_number = QString::fromStdString(constructSalesPhoneNumber().at(1));

    emit contactChanged();
}

void ContactManager::setSales(
        const QString &name,
        const QString &street,
        const QString &city,
        const QString &state,
        const QString &postalCode,
        const QString &email,
        const QString &phoneNumber
        )
{
    if (m_salesCsvManager.getNumEntries() > 0)
    {
        for (int i = 0; i < number_of_entries; i++)
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

    m_salesCsvManager.createRecord(vector1.data());
    m_salesCsvManager.createRecord(vector2.data());
    m_salesCsvManager.createRecord(vector3.data());
    m_salesCsvManager.createRecord(vector4.data());
    m_salesCsvManager.createRecord(vector5.data());
    m_salesCsvManager.createRecord(vector6.data());
    m_salesCsvManager.createRecord(vector7.data());

    emit contactChanged();

    qInfo() << "NVENT"
            << ","
            << "CONTACTS"
            << ","
            << "Sales Contact Information: " +
               m_sales_company_name.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_sales_street.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_sales_city.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_sales_state +
               "; " +
               m_sales_postal_code +
               "; " +
               m_sales_email.replace(QString::fromStdString(","), QString::fromStdString(";")) +
               "; " +
               m_sales_phone_number +
               ".";
}

std::vector<std::string> ContactManager::constructSalesCompanyName()
{
    const int cvs_index = 0;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {COMPANY,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructSalesStreet()
{
    const int cvs_index = 1;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {STREET,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructSalesCity()
{
    const int cvs_index = 2;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {CITY,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructSalesState()
{
    const int cvs_index = 3;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() != 2 || vector.at(1).length() != 2)
    {
        vector = {STATE,"**"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructSalesPostalCode()
{
    const int cvs_index = 4;
    const int postal_code_length = 5;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() != 2 || vector.at(1).length() != postal_code_length)
    {
        vector = {POSTAL_CODE,"*****"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructSalesEmail()
{
    const int cvs_index = 5;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() < 2)
    {
        vector = {EMAIL,"TBD"};
    }

    return vector;
}

std::vector<std::string> ContactManager::constructSalesPhoneNumber()
{
    const int cvs_index = 6;
    const int phone_number_length = 13;
    std::vector<std::string> vector = m_salesCsvManager.readRecord(cvs_index);

    if (vector.size() != 2 || vector.at(1).length() != phone_number_length)
    {
        vector = {PHONE_NUMBER,"(***)***-****"};
    }

    return vector;
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


