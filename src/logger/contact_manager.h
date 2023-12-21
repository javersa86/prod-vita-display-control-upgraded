#pragma once
#include "csv_manager.h"
#include <QVector>
#include <QObject>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QByteArray>
#include <QLocale>
#include <QTimer>

/**
 * @addtogroup contactManagerModule
 * @{
 */

/**
 * @brief Constant title for service contact csv file.
 */
constexpr const char* SERVICE_CONTACT_FILE = "service_contact_information.csv";

/**
 * @brief Constant title for sales contact csv file.
 */
constexpr const char* SALES_CONTACT_FILE = "sales_contact_information.csv";

/**
 * @brief Constant string for company.
 */
constexpr const char* COMPANY = "COMPANY";

/**
 * @brief Constant string for street.
 */
constexpr const char* STREET = "STREET";

/**
 * @brief Constant string for city.
 */
constexpr const char* CITY = "CITY";

/**
 * @brief Constant string for state.
 */
constexpr const char* STATE = "STATE";

/**
 * @brief Constant string for postal code.
 */
constexpr const char* POSTAL_CODE = "POSTAL CODE";

/**
 * @brief Constant string for email.
 */
constexpr const char* EMAIL = "EMAIL";

/**
 * @brief Constant string for phone number.
 */
constexpr const char* PHONE_NUMBER = "PHONE NUMBER";

/**
 * @file contact_manager.h
 * @brief Header file for the contact_manager.cpp with info.
 */

/**
 * @file contact_manager.cpp
 * @brief Manager allows technician to update the contact information for the service company and the company that sells the Nvent-Vita.
 * @note Values are saved on .csv files.
 */

/**
 * @brief The ContactManager class
 */
class ContactManager: public QObject
{
    /**
     * @addtogroup contactManagerModule
     * @{
     */

    Q_OBJECT

    /**
     * @brief serviceCompanyName
     */
    Q_PROPERTY(QString serviceCompanyName READ getServiceCompanyName NOTIFY contactChanged)
    /**
     * @brief serviceStreet
     */
    Q_PROPERTY(QString serviceStreet READ getServiceStreet NOTIFY contactChanged)
    /**
     * @brief serviceCity
     */
    Q_PROPERTY(QString serviceCity READ getServiceCity NOTIFY contactChanged)
    /**
     * @brief serviceState
     */
    Q_PROPERTY(QString serviceState READ getServiceState NOTIFY contactChanged)
    /**
     * @brief servicePostal
     */
    Q_PROPERTY(QString servicePostalCode READ getServicePostalCode NOTIFY contactChanged)
    /**
     * @brief serviceEmail
     */
    Q_PROPERTY(QString serviceEmail READ getServiceEmail NOTIFY contactChanged)
    /**
     * @brief servicePhoneNumber
     */
    Q_PROPERTY(QString servicePhoneNumber READ getServicePhoneNumber NOTIFY contactChanged)

    /**
     * @brief salesCompanyName
     */
    Q_PROPERTY(QString salesCompanyName READ getSalesCompanyName NOTIFY contactChanged)
    /**
     * @brief salesCompanyStreet
     */
    Q_PROPERTY(QString salesStreet READ getSalesStreet NOTIFY contactChanged)
    /**
     * @brief salesCity
     */
    Q_PROPERTY(QString salesCity READ getSalesCity NOTIFY contactChanged)
    /**
     * @brief salesState
     */
    Q_PROPERTY(QString salesState READ getSalesState NOTIFY contactChanged)
    /**
     * @brief salesPostalCode
     */
    Q_PROPERTY(QString salesPostalCode READ getSalesPostalCode NOTIFY contactChanged)
    /**
     * @brief salesEmail
     */
    Q_PROPERTY(QString salesEmail READ getSalesEmail NOTIFY contactChanged)
    /**
     * @brief salesPhoneNumber
     */
    Q_PROPERTY(QString salesPhoneNumber READ getSalesPhoneNumber NOTIFY contactChanged)

    public:
        /**
         * @brief Constructor Method and constructs CSV Managers.
         * @param parent
         */
        ContactManager(QObject *parent = nullptr);

        /**
         * @brief Gets Company Name for Service Company.
         * @return QString
         */
        QString getServiceCompanyName();

        /**
         * @brief Gets Street Address for Service Company.
         * @return QString
         */
        QString getServiceStreet();

        /**
         * @brief Gets Town / City for Service Company.
         * @return QString
         */
        QString getServiceCity();

        /**
         * @brief Gets State for Service Company.
         * @return QString
         */
        QString getServiceState();

        /**
         * @brief Gets Postal Code / ZipCode for Service Company.
         * @return QString
         */
        QString getServicePostalCode();

        /**
         * @brief Gets email / website for Service Company.
         * @return QString
         */
        QString getServiceEmail();

        /**
         * @brief Gets phone number for Service Company.
         * @return QString
         */
        QString getServicePhoneNumber();

        /**
         * @brief Gets Company name for Sales Company.
         * @return QString
         */
        QString getSalesCompanyName();

        /**
         * @brief Gets Street Address for Sales Company.
         * @return QString
         */
        QString getSalesStreet();

        /**
         * @brief Gets Town / City for Sales Company.
         * @return QString
         */
        QString getSalesCity();

        /**
         * @brief Gets State for Sales Company.
         * @return QString
         */
        QString getSalesState();

        /**
         * @brief Gets Postal Code / ZipCode for Sales Company.
         * @return QString
         */
        QString getSalesPostalCode();

        /**
         * @brief Gets email / website for Sales Company.
         * @return QString
         */
        QString getSalesEmail();

        /**
         * @brief Gets phone number for Sales Company.
         * @return QString
         */
        QString getSalesPhoneNumber();

    public slots:

        /**
         * @brief Sets all contact information for Service Company, for the .csv file needs to be recreated each time.
         * @param name
         * @param street
         * @param city
         * @param state
         * @param postalCode
         * @param email
         * @param phoneNumber
         * @callergraph
         */
        void setService(
                const QString &name,
                const QString &street,
                const QString &city,
                const QString &state,
                const QString &postalCode,
                const QString &email,
                const QString &phoneNumber
                );

        /**
         * @brief ContactManager::setSales
         * @param name
         * @param street
         * @param city
         * @param state
         * @param postalCode
         * @param email
         * @param phoneNumber
         * @callergraph
         *
         * Sets all contact information for Sales Company.
         * .csv file need to be recreated each time.
         */
        void setSales(
                const QString &name,
                const QString &street,
                const QString &city,
                const QString &state,
                const QString &postalCode,
                const QString &email,
                const QString &phoneNumber
                );

    signals:
        /**
         * @brief Sends signal for when contact information is changed.
         * @callgraph
         */
        void contactChanged();

        /**
         * @brief Sends signal for keyboard input when updating contact information.
         * @param value
         * @callgraph
         */
        void addKeySignal(QString value);

        /**
         * @brief Sends signal for delete key input when updating contact information.
         * @callgraph
         */
        void deleteKeySignal();

        /**
         * @brief Sends signal for enter key input when updating contact information.
         * @callgraph
         */
        void enterKeySignal();

        /**
         * @brief Sends signal for shift key input when updating contact information.
         * @param state
         * @callgraph
         */
        void shiftKeySignal(int state);

        /**
         * @brief Sends signal for switch key input when updating contact information.
         * @param state
         * @callgraph
         */
        void switchKeySignal(int state);

        /**
         * @brief Sends signal for cancel key input when updating contact information.
         * @callgraph
         */
        void cancelKeySignal();

        /**
         * @brief Sends signal for done key input when updating contact information.
         * @callgraph
         */
        void doneKeySignal();

        /**
         * @brief Sends signal for caps lock input when udpating contact information.
         * @param value
         * @callgraph
         */
        void allCapKeySignal(int value);

    private:

        CSVManager m_serviceCsvManager;
        CSVManager m_salesCsvManager;

        QString m_service_company_name;
        QString m_service_street;
        QString m_service_city;
        QString m_service_state;
        QString m_service_postal_code;
        QString m_service_email;
        QString m_service_phone_number;

        QString m_sales_company_name;
        QString m_sales_street;
        QString m_sales_city;
        QString m_sales_state;
        QString m_sales_postal_code;
        QString m_sales_email;
        QString m_sales_phone_number;

        const int number_of_entries = 7;

        /**
         * @brief Retrieves contact information for service company from .csv file.
         * @details Stores the current variables for service contact information, which includes the following:
         *  - Company Name
         *  - Street Address
         *  - Town / City
         *  - State
         *  - Postal Code / ZipCode
         *  - email / website
         *  - phone number
         *  @note Updates when device powers on or whenever info changes.
         */
        void updateServiceContact();

        /**
         * @brief  Retrieves contact information for sales company from .csv file.
         * @details Stores the current variables for sales contact information, which includes the following:
         *  - Company Name
         *  - Street Address
         *  - Town / City
         *  - State
         *  - Postal Code / ZipCode
         *  - email / website
         *  - phone number
         *  @note Updates when device powers on or whenever info changes.
         */
        void updateSalesContact();

        /**
         * @brief Constructs and returns string from vector that is greater than 2 entries.
         * @param vector
         * @return QString
         */
        static QString getFullString(std::vector<std::string> vector);

        std::vector<std::string> constructServiceCompanyName();
        std::vector<std::string> constructServiceStreet();
        std::vector<std::string> constructServiceCity();
        std::vector<std::string> constructServiceState();
        std::vector<std::string> constructServicePostalCode();
        std::vector<std::string> constructServiceEmail();
        std::vector<std::string> constructServicePhoneNumber();

        std::vector<std::string> constructSalesCompanyName();
        std::vector<std::string> constructSalesStreet();
        std::vector<std::string> constructSalesCity();
        std::vector<std::string> constructSalesState();
        std::vector<std::string> constructSalesPostalCode();
        std::vector<std::string> constructSalesEmail();
        std::vector<std::string> constructSalesPhoneNumber();
        /** @} */
};

/** @} */
