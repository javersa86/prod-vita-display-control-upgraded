#pragma once
#include <string>
#include <fstream>
#include <QObject>
#include <QFile>
#include <QDataStream>
#include <QTextStream>

/**
 * @addtogroup brightnessManagerModule
 * @{
 */

/**
 * @file brightness_manager.h
 * @brief Header file for brightness_manager.cpp with info.
 */

/**
 * @file brightness_manager.cpp
 * @brief Manages the brightness of the display.
 */

/**
 * @brief The BrightnessManager class
 */
class BrightnessManager : public QObject
{
    /**
     * @addtogroup brightnessManagerModule
     * @{
     */

    Q_OBJECT
    public:

        /**
         * @brief Brightness Constructor
         * @details This class manages the brightness of the display screen.
         *          In Linux, the brightness is controlled by a file in the file system.
         *          In our case, /sys/class/backlight/backlight/brightness.
         * @param parent
         */
        BrightnessManager(QObject *parent = nullptr);

    public slots:

        /**
         * @brief Gets the current brightness from the file as a percentage.
         * @return double
         * @callergraph
         */
        double getBrightness();

        /**
         * @brief Sets the brightness to percentage (in our case percentage of 64) and writes that value to the brightness file.
         * @param value
         * @callergraph
         */
        void changeBrightness(double value);

        /**
         * @brief Gets the max brightness percentage.
         * @return int
         * @callergraph
         */
        int getMaxPercent() const;

        /**
         * @brief Gets the min brightness percentage.
         * @return int
         * @callergraph
         */
        int getMinPercent() const;


    signals:
        /**
         * @brief Signal emitted when brightness changed.
         * @callgraph
         */
        void brightnessChanged();

    private:
        QString m_file;
        double m_max;
        const int m_max_percent = 100;
        const int m_min_percent = 20;

        /**
         * @brief Get the maximum value of the brightness, located in the max_brightness file.
         * @return int
         */
        static int getMax();
        /** @} */
};

/** @} */
