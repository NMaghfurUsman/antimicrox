/* antimicrox Gamepad to KB+M event mapper
 * Copyright (C) 2015 Travis Nickles <nickles.travis@gmail.com>
 * Copyright (C) 2020 Jagoda Górska <juliagoda.pl@protonmail>
 * Copyright (C) 2021 Paweł Kotiuk <kotiuk@zohomail.eu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

class QCommandLineParser;

#include <QApplication>

#include "logger.h"

class ControllerOptionsInfo
{
  public:
    ControllerOptionsInfo()
    {
        controllerNumber = 0;
        startSetNumber = 0;
        unloadProfile = false;
    }

    bool hasProfile() { return !profileLocation.isEmpty(); }

    QString getProfileLocation() { return profileLocation; }

    void setProfileLocation(QString location) { profileLocation = location; }

    bool hasControllerNumber() { return (controllerNumber > 0); }

    int getControllerNumber() { return controllerNumber; }

    void setControllerNumber(int temp) { controllerNumber = temp; }

    bool hasControllerID() { return !controllerIDString.isEmpty(); }

    QString getControllerID() { return controllerIDString; }

    void setControllerID(QString temp) { controllerIDString = temp; }

    bool isUnloadRequested() { return unloadProfile; }

    void setUnloadRequest(bool status) { unloadProfile = status; }

    int getStartSetNumber() { return startSetNumber; }

    int getJoyStartSetNumber() { return startSetNumber - 1; }

    void setStartSetNumber(int temp)
    {
        if ((temp >= 1) && (temp <= 24))
        {
            startSetNumber = temp;
        }
    }

  private:
    QString profileLocation;
    int controllerNumber;
    QString controllerIDString;
    int startSetNumber;
    bool unloadProfile;
};

class CommandLineUtility : public QObject
{
    Q_OBJECT

  public:
    explicit CommandLineUtility(QObject *parent = nullptr);

    /**
     * @brief load and parse arguments from commandline
     *
     * @param parsed_app
     * @exception std::runtime_error - in case of problems with parsing like unknown flag, wrong value etc
     */
    void parseArguments(const QApplication &parsed_app);

    bool isLaunchInTrayEnabled();
    bool isTrayHidden();
    bool hasProfile();
    bool hasControllerNumber();
    bool hasControllerID();
    bool isHiddenRequested();
    bool isShowRequested();
    bool isUnloadRequested();
    bool shouldListControllers();
    bool hasProfileInOptions();

    int getControllerNumber();
    int getStartSetNumber();
    int getJoyStartSetNumber();

    QString getControllerID();
    QString getProfileLocation();
    QString getEventGenerator();
    QString getCurrentLogFile();

    QList<int> *getJoyStartSetNumberList();
    QList<ControllerOptionsInfo> const &getControllerOptionsList();

    Logger::LogLevel getCurrentLogLevel();

  protected:
  private:
    bool launchInTray;
    bool hideTrayIcon;
    bool hiddenRequest;
    bool showRequest;
    bool unloadProfile;
    bool listControllers;

    int startSetNumber;
    int controllerNumber;
    int currentListsIndex;

    QString profileLocation;
    QString controllerIDString;
    QString eventGenerator;
    QString currentLogFile;

    Logger::LogLevel currentLogLevel;

    QList<ControllerOptionsInfo> controllerOptionsList;

    static QStringList eventGeneratorsList;

    void parseArgsProfile(const QCommandLineParser &parser);
    void parseArgsPrControle(const QCommandLineParser &parser);
    void parseArgsUnload(const QCommandLineParser &parser);
    void parseArgsStartSet(const QCommandLineParser &parser);
};

#endif // COMMANDLINEPARSER_H
