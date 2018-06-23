//*********************************************************************************************************************************
//
// PROJECT:							gnuCash
// FILE:								main application
// SUBSYSTEM:						main(...)
// LANGUAGE:						C++
// TARGET OS:						UNIX/LINUX/WINDOWS/MAC
// LIBRARY DEPENDANCE:	Qt
// AUTHOR:							Gavin Blakeman (GGB)
// LICENSE:             GPLv2
//
//                      Copyright 2018 Gavin Blakeman.
//                      This file is part of the gnuCash SharePrice Upload application
//
//                      gnuCash is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
//                      License as published by the Free Software Foundation, either version 2 of the License, or (at your option)
//                      any later version.
//
//                      gnuCash is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
//                      warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//                      more details.
//
//                      You should have received a copy of the GNU General Public License along with gnuCash.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:            Implements the main(...) function
//
// HISTORY:             2018-03-30/GGB - Development of classes for gnuCash
//
//*********************************************************************************************************************************

  // Standard C++ library headers.

#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

  // Qt Library headers

#include <Qt>
#include <QCoreApplication>

  // Miscellaneous library headers

//#include <boost/algorithm/string.hpp>
//#include <boost/asio/ip/address_v4.hpp>
//#include <boost/chrono.hpp>
//#include <boost/iostreams/tee.hpp>
//#include <boost/iostreams/stream.hpp>
//#include <boost/lexical_cast.hpp>
//#include <boost/program_options.hpp>
#include <GCL>

  // gnuCash headers

#include "../include/databaseGnuCash.h"

///// @brief Main function for the application.
///// @param[in] argc
///// @param[in] argv
///// @returns Exit code.
///// @version 2018-03-30/GGB - Function created.

int main(int argc, char *argv[])
{
  int returnValue = -1;

  boost::filesystem::path ifn;
  boost::filesystem::ifstream ifs;
  std::string dbDriver;
  std::string dbIPAddr;
  int dbPort;
  std::string dbName;
  std::string dbUser;
  std::string dbPassword;
  DCommodityValues commodityValues;
  std::string shareName;
  std::string currencyName;
  CGnuCashDatabase gnuCashDatabase;

  try
  {

    GCL::logger::PLoggerSink coutLogger(new GCL::logger::CStreamSink(std::cout));
    GCL::logger::defaultLogger().addSink(coutLogger);

    INFOMESSAGE("gnuCash: Share Price Upload");
    INFOMESSAGE("Version: 2018-03");
    INFOMESSAGE("Copyright 2018 Gavin Blakeman");

    //  boost::program_options::options_description cmdLine("Allowed Options");
    //  cmdLine.add_options()
    //      ("help,h", "produce help message")
    //      ("dbdriver", boost::program_options::value<std::string>(&dbDriver)->default_value("MYSQL"), "database type <MYSQL>")
    //      ("dbip", boost::program_options::value<std::string>(&dbIPAddr)->default_value("localhost"), "database host address <localhost>")
    //      ("dbport", boost::program_options::value<int>(&dbPort)->default_value(3306), "database port <3306>")
    //      ("dbname", boost::program_options::value<std::string>(&dbName)->default_value("GNUCASH"), "database name <GNUCASH>")
    //      ("dbuser", boost::program_options::value<std::string>(&dbUser)->default_value("GNUCASH"), "database username <GNUCASH>")
    //      ("dbpassword", boost::program_options::value<std::string>(&dbPassword)->default_value("GNUCASH"), "database password <GNUCASH>")
    //      ("file", boost::program_options::value<boost::filesystem::path>(&ifn),"File Name with Share Price Data")
    //      ("share", boost::program_options::value<std::string(&shareName), "Share Name")
    //      ("version,v", "Display version and status information.")
    //      ("debug", "Display debug information.")
    //      ("trace", "Capture Trace Information.")
    //      ;

    //  boost::program_options::variables_map vm;
    //  boost::program_options::store(boost::program_options::command_line_parser(argc, argv).
    //                                options(cmdLine)
    //                                .run(), vm);
    //  boost::program_options::notify(vm);

    //  if (vm.count("help"))
    //  {
    //    std::cout << cmdLine << std::endl;
    //    GCL::logger::defaultLogger().shutDown();
    //    return 0;
    //  };

    if (!boost::filesystem::exists(ifn))
    {
      ERRORMESSAGE("Input file not found.");
      throw xxx;
    };

    //  QCoreApplication app(argc, argv);

    if (!gnuCashDatabase.createConnection(QString::fromStdString(dbDriver), QString::fromStdString(dbIPAddr), dbPort,
                                          QString::fromStdString(dbName), QString::fromStdString(dbUser),
                                          QString::fromStdString(dbPassword)) )
    {
      ERRORMESSAGE("Unable to connect to database.");
      throw xxx;
    }

    ifs.open(ifn);

    while (!ifs.eof())
    {
      std::string szLine;
      std::size_t indexStart= 0, indexEnd = 0;
      std::string szClose;
      std::string szDate;
      std::string szTemp;

      std::getline(ifs, szLine);

      // Decompose the line into the relevant values.
      // Line is in the format "date, open, high, low, close, adj close, volume"
      // We only need date and close.

      //    indexEnd = szLine.find(",", indexStart);

      // Date

      szDate = szLine.substr(indexStart, indexEnd);
      //    indexStart = indexEnd + 1;

      // open

      //    indexEnd = szLine.find(",", indexStart);
      //    indexStart = indexEnd + 1;

      // high

      //    indexEnd = szLine.find(",", indexStart);
      //    indexStart = indexEnd + 1;

      // low

      //    indexEnd = szLine.find(",", indexStart);
      //    indexStart = indexEnd + 1;

      // close

      //     indexEnd = szLine.find(",", indexStart);

      szClose = szLine.substr(indexStart, indexEnd);

      // Now parse the strings and create the commodity entry.


      try
      {
        SCommodityValue commodityValue;

        szDate.trim(szDate);
        szClose.trim(szClose);

        // Date should be in form yyyy-mm-dd.

        indexStart = 0;
        indexEnd = szDate.find("-", indexStart);
        szTemp = szDate.substr(indexStart, indexEnd);
        commodityValue.year = boost::lexical_cast<std::uint16_t>(szYear);

        indexStart = indexEnd + 1;
        indexEnd = szDate.find("-", indexStart);
        szTemp = szDate.substr(indexStart, indexEnd);
        commodityValue.month = boost::lexical_cast<std::uint8_t>(szYear);

        indexStart = indexEnd + 1;
        indexEnd = szDate.size();
        szTemp = szDate.substr(indexStart, indexEnd);
        commodityValue.day = boost::lexical_cast<std::uint8_t>(szYear);

        commodityValue.type = "last";
        commodityValue.source = "Finance::Quote";
        commodityValue.value = boost::lexical_cast<double>(szClose);

        commodityValues.push_back(commodityValue);
      }
      catch(...)
      {

      }
    };    // while statement.


    gnuCashDatabase.writeCurrencyValues(commodityValues, shareName, currencyName);

  }
  catch (...)
  {

  }


  return returnValue;
}

