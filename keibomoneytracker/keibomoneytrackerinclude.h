/*
* Copyright © 2020 Carlos Constancio Dominguez Martinez
*
* This file is part of Keibo-MoneyTracker
*
* Keibo-MoneyTracker is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Keibo-MoneyTracker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
* Authored by: Carlos Constancio Dominguez Martinez <dmartinez.carlos@gmail.com>
*/

#ifndef BUYDATAINCLUDE_H
#define BUYDATAINCLUDE_H
#include <string>
#include <sstream>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------////-----------------------------------------------------------------------------------------//

///GLOBAL DEFINES
const int  NUMBER_OF_CURRENCIES = 24;
enum Currency   {DOLLAR, EURO, FRANC, KORUNA, KUNA, KRONA, KRONE, LIRA, MANAT, NAIRA, NEWSHECKEL, PESO, POUND, RAND, REAL, RIYAL, RUBLE, RUBLE_BELARUS, RUPEE, SOL, WON, YEN, YUAN, ZLOTY};
enum Language   {ENGLISH, GERMAN, SPANISH};
enum RepetitionOption {DO_NOT_REPEAT, REPEAT_EVERY_WEEK, REPEAT_EVERY_TWO_WEEKS, REPEAT_EVERY_MONTH};

namespace Months
{
    const int JANUARY     = 0;
    const int FEBRUARY    = 1;
    const int MARCH       = 2;
    const int APRIL       = 3;
    const int MAY         = 4;
    const int JUNE        = 5;
    const int JULY        = 6;
    const int AUGUST      = 7;
    const int SEPTEMBER   = 8;
    const int OCTOBER     = 9;
    const int NOVEMBER    = 10;
    const int DECEMBER    = 11;
}

inline std::string getCurrenySymbol (const Currency &iCurrency)
{
    switch (iCurrency) {
    case DOLLAR:
        return "$";
    case EURO:
        return "€";
    case FRANC:
        return "Fr.";
    case PESO:
        return "$";
    case YEN:
        return "¥";
    case POUND:
        return "£";
    case RUBLE:
        return "₽";
    case KRONE:
        return "kr";
    case RUPEE:
        return "₹";
    case NEWSHECKEL:
        return "₪";
    case RAND:
        return "R";
    case ZLOTY:
        return "zł";
    case YUAN:
        return "¥";
    case REAL:
        return "R$";
    case KUNA:
        return "kn";
    case LIRA:
        return "₺";
    case MANAT:
        return "₼";
    case SOL:
        return "S/.";
    case RUBLE_BELARUS:
        return "Br";
    case NAIRA:
        return "₦";
    case KRONA:
        return "kr";
    case RIYAL:
        return "QR";
    case KORUNA:
        return "Kč";
    case WON:
        return "₩";
    default:
        return "No currency available";
    }    
}

inline std::string getDateInLanguageFormat(const int &day, const int &month, const int &year, const Language &language)
{
    std::string finalString = "";
    if (language == ENGLISH){
        std::string stringDay   = std::to_string(day);
        std::string stringMonth = std::to_string(month+1);
        std::string stringYear  = std::to_string(year);

        std::string zeroDay = "";
        if (day < 10){
            zeroDay = "0";
        }
        std::string zeroMonth = "";
        if (month < 10){
            zeroMonth = "0";
        }

        finalString = zeroMonth+stringMonth+"/"+zeroDay+stringDay+"/"+stringYear;
    }
    else if (language == GERMAN){
        std::string stringDay   = std::to_string(day);
        std::string stringMonth = std::to_string(month+1);
        std::string stringYear  = std::to_string(year);

        std::string zeroDay = "";
        if (day < 10){
            zeroDay = "0";
        }
        std::string zeroMonth = "";
        if (month < 10){
            zeroMonth = "0";
        }

        finalString = zeroDay+stringDay+"."+zeroMonth+stringMonth+"."+stringYear;
    }
    else if (language == SPANISH){
        std::string stringDay   = std::to_string(day);
        std::string stringMonth = std::to_string(month+1);
        std::string stringYear  = std::to_string(year);

        std::string zeroDay = "";
        if (day < 10){
            zeroDay = "0";
        }
        std::string zeroMonth = "";
        if (month < 10){
            zeroMonth = "0";
        }

        finalString = zeroDay+stringDay+"/"+zeroMonth+stringMonth+"/"+stringYear;
    }

    return finalString;
}

inline double getAveragePerMonthInInterval(const double &totalAmount, const int &firstMonthOfFirstYear, const int &firstYear, const int &lastMonthOfLastYear, const int &lastYear)
{
    int totalNumberOfMonths = 0;
    double averagePerMonth = 0.0;

    if (firstYear == lastYear){
        totalNumberOfMonths = (lastMonthOfLastYear+1)-firstMonthOfFirstYear;
    } else if (firstYear < lastYear) {
        for (int x = firstYear; x <= lastYear; ++x){
            if (x == firstYear){
                totalNumberOfMonths += (12-firstMonthOfFirstYear);
            }
            else if ((x < lastYear) && (x > firstYear) ){
                totalNumberOfMonths += 12;
            }
            else if (x == lastYear){
                totalNumberOfMonths += (lastMonthOfLastYear+1);
            }
        }
    }

    if (totalAmount > 0.0){
        averagePerMonth = totalAmount/totalNumberOfMonths;
    }

    return averagePerMonth;
}

inline std::string getMonthInLanguage(const int &monthId, const Language &currentLanguage)
{
    if (currentLanguage == ENGLISH)
    {
        switch (monthId) {
            case 0:
                return "January";
            case 1:
                return "February";
            case 2:
                return "March";
            case 3:
                return "April";
            case 4:
                return "May";
            case 5:
                return "June";
            case 6:
                return "July";
            case 7 :
                return "August";
            case 8:
                return "September";
            case 9:
                return "October";
            case 10:
                return "November";
            case 11:
                return "December";
            default:
            return "";
        }
    }
    if (currentLanguage == GERMAN)
    {
        switch (monthId) {
            case 0:
                return "Januar";
            case 1:
                return "Februar";
            case 2:
                return "März";
            case 3:
                return "April";
            case 4:
                return "Mai";
            case 5:
                return "Juni";
            case 6:
                return "Juli";
            case 7 :
                return "August";
            case 8:
                return "September";
            case 9:
                return "Oktober";
            case 10:
                return "November";
            case 11:
                return "Dezember";
            default:
            return "";
        }
    }
    if (currentLanguage == SPANISH)
    {
        switch (monthId) {
            case 0:
                return "Enero";
            case 1:
                return "Febrero";
            case 2:
                return "Marzo";
            case 3:
                return "Abril";
            case 4:
                return "Mayo";
            case 5:
                return "Junio";
            case 6:
                return "Julio";
            case 7 :
                return "Agosto";
            case 8:
                return "Septiembre";
            case 9:
                return "Octubre";
            case 10:
                return "Noviembre";
            case 11:
                return "Diciembre";
            default:
            return "";
        }
    }
    return "";
}

inline int getNumberOfDaysInMonth(int Year, int Month)
{
        //leap year condition, if month is 1 (february)
        if( Month == 1)
        {
            if((Year%400==0) || (Year%4==0 && Year%100!=0))
                return 29;
            else
                return 28;
        }
        //months which has 31 days
        else if(Month == 0 || Month == 2 || Month == 4 || Month == 6 || Month == 7
        ||Month == 9 || Month==11)
            return 31;
        else
            return 30;
}

inline std::string getAmountAsStringInGermanFormat(const double &amount, int _precision = 2)
{
    int numberOfDecimals = 0;
    std::ostringstream tmpstream;
    tmpstream.precision(_precision);
    tmpstream <<std::fixed<<amount;  //get only two numbers after decimal point
    std::string tempString = tmpstream.str();
    std::string finalString = "";
    bool pointFound = false;
    for (size_t i = 0; i != tempString.size(); ++i)
    {
        if (numberOfDecimals >= 2){
            break;
        }
        if (pointFound)
        {
            ++numberOfDecimals;
        }
        if (tempString[i] == '.' || tempString[i] == ','){
            tempString[i] = ',';
            pointFound = true;
        }
        finalString += tempString[i];
    }

    int counter = 0;
    std::string amountFormattedBackwards;
    amountFormattedBackwards.clear();
    for (std::string::reverse_iterator itStr = finalString.rbegin();  //Count from left to right to separate in groups of three digits after decimal point.
         itStr != finalString.rend(); ++itStr)
    {
        if (*itStr == '-') {
            amountFormattedBackwards += *itStr;
            continue;
        }
        if (*itStr == '.' || *itStr == ','){ //If a point or comma is found, just add it, reset digit counter and go to next iteration
            amountFormattedBackwards += *itStr;
            counter = 0;
            continue;
        }
        if (counter > 2){   //If three digits are counted (including zero) add a space, reset counter and allow addition of current digit
            amountFormattedBackwards += '.';
            counter = 0;
        }
        ++counter;
        amountFormattedBackwards += *itStr;
    }

    std::string amountFormattedForwards;
    amountFormattedForwards.clear();
    for (std::string::reverse_iterator itStr = amountFormattedBackwards.rbegin();
         itStr != amountFormattedBackwards.rend(); ++itStr)
    {
        amountFormattedForwards += *itStr;
    }

    return amountFormattedForwards;
}

inline std::string getAmountAsStringFormatted(const double &amount, int _precision = 2) //Separate the digits of amounts in groups of three after decimal point.
{
    //Reverse iterators
    std::ostringstream tmpstream;
    tmpstream.precision(_precision);
    tmpstream <<std::fixed<<amount;  //get only two numbers after decimal point
    std::string amountStr = tmpstream.str();
    std::string amountFormattedBackwards;
    amountFormattedBackwards.clear();
    int counter = 0;

    for (std::string::reverse_iterator itStr = amountStr.rbegin();  //Count from left to right to separate in groups of three digits after decimal point.
         itStr != amountStr.rend(); ++itStr)
    {
        if (*itStr == '-') {
            amountFormattedBackwards += *itStr;
            continue;
        }
        if (*itStr == '.' || *itStr == ','){ //If a point or comma is found, just add it, reset digit counter and go to next iteration
            amountFormattedBackwards += *itStr;
            counter = 0;
            continue;
        }
        if (counter > 2){   //If three digits are counted (including zero) add a space, reset counter and allow addition of current digit
            amountFormattedBackwards += ',';
            counter = 0;
        }
        ++counter;
        amountFormattedBackwards += *itStr;
    }

    std::string amountFormattedForwards;
    amountFormattedForwards.clear();
    for (std::string::reverse_iterator itStr = amountFormattedBackwards.rbegin();
         itStr != amountFormattedBackwards.rend(); ++itStr)
    {
        amountFormattedForwards += *itStr;
    }

    return amountFormattedForwards;
}

///COLOR CONFIGURATION CLASS - IT STORES ALL COLORS THAT A SET/CONFIGURATION CAN HAVE
const int NUMBER_OF_MAX_CONFIGURATIONS = 6;
struct ColorConfiguration
{
    //Constructor requires a color theme name
    ColorConfiguration() = default;
    ColorConfiguration(const std::string &themeName) : colorThemeName(themeName) {}

    bool showMonthlyAmountsInColor   = true;
    std::string colorThemeName       = "";

    int colorBarIncomeSelected       = 13;
    int colorBarIncomeUnselected     = 4;
    int colorBarExpensesSelected     = 9;
    int colorBarExpensesUnselected   = 7;
    int colorBarBackground           = 36;

    int colorGroupIncomeSelected     = 13;
    int colorGroupIncomeUnselected   = 4;
    int colorGroupExpensesSelected   = 9;
    int colorGroupExpensesUnselected = 16;
    int colorGroupIncomeBackground   = 8;
    int colorGroupExpensesBackground = 8;

    int colorTableIncomeAmount       = 13;

    bool useDarkOverallTheme = false;
    int colorOverallBackground    = 37; //Possible values should be 37(Light) and 38(Dark)
    int colorOverallText          = 39; //Possible values should be 39(Light) and 40(Dark)
    int colorHighlightedBorders   = 41; //Possible values should be 41(Light) and 42(Dark)

    inline void setOverallThemeColors()
    {
        if (useDarkOverallTheme){
            colorOverallBackground    = 38;
            colorOverallText          = 40;
            colorHighlightedBorders   = 42;
        }
        else {
            colorOverallBackground    = 37;
            colorOverallText          = 39;
            colorHighlightedBorders   = 41;
        }
    }
};

const int NUMBER_OF_POSSIBLE_COLORS = 43;  //All colors + transparent(36)
inline void getColorCode(int colorID, int &R, int &G, int &B) {
    switch (colorID) {
    case 0:
    {   R = 255;  G = 121;  B = 111;
        break;
    }
    case 1:
    {   R = 252;  G = 175;  B = 62;
        break;
    }
    case 2:
    {   R = 255;  G = 233;  B = 79;
        break;
    }
    case 3:
    {
        R = 175;  G = 210;  B = 116; //Current
        //R = 189;  G = 183;  B = 107; //Khaki
        break;
    }
    case 4:
    {
        R = 200;  G = 231;  B = 227;
        break;
    }
    case 5:
    {   R = 114;  G = 159;  B = 207;
        break;
    }
    case 6:
    {   R = 173;  G = 127;  B = 168;
        break;
    }
    case 7:
    {
        R = 251;  G = 238;  B = 193;
        break;
    }
    case 8:
    {
        R = 234;  G = 232;  B = 220;
        break;
    }
    case 9:
    {   R = 239;  G = 45;  B = 45;
        break;
    }
    case 10:
    {
        R = 255;  G = 128;  B = 51;
        break;
    }
    case 11:
    {   R = 245;  G = 220;  B = 0;
        break;
    }
    case 12:
    {
        R = 138;  G = 226;  B = 52;
        break;
    }
    case 13:
    {   R = 0;  G = 155;  B = 165;
        break;
    }
    case 14:
    {   R = 52;  G = 101;  B = 164;
        break;
    }
    case 15:
    {   R = 117;  G = 80;  B = 123;
        break;
    }
    case 16:
    {
        R = 218;  G = 173;  B = 134;
        break;
    }
    case 17:
    {   R = 136;  G = 138;  B = 133;
        break;
    }
    case 18:
    {   R = 235;  G = 0;  B = 0;
        break;
    }
    case 19:
    {
        R = 245;  G = 121;  B = 0;
        break;
    }
    case 20:
    {   R = 198;  G = 165;  B = 0;
        break;
    }
    case 21:
    {   R = 78;  G = 154;  B = 6;
        break;
    }
    case 22:
    {
        R = 16;  G = 100;  B = 102;
        break;
    }
    case 23:
    {   R = 30;  G = 50;  B = 135;
        break;
    }
    case 24:
    {   R = 92;  G = 53;  B = 102;
        break;
    }
    case 25:
    {
        R = 189;  G = 172;  B = 102;
        break;
    }
    case 26:
    {   R = 60;  G = 65;  B = 69;
        break;
    }
    case 27:
    {   R = 165;  G = 0;  B = 0;
        break;
    }
    case 28:
    {
        R = 206;  G = 92;  B = 0;
        break;
    }
    case 29:
    {   R = 152;  G = 130;  B = 0;
        break;
    }
    case 30:
    {   R = 15;  G = 125;  B = 5;
        break;
    }
    case 31:
    {
        R = 32;  G = 64;  B = 85;
        break;
    }
    case 32:
    {   R = 10;  G = 18;  B = 98;
        break;
    }
    case 33:
    {   R = 80;  G = 31;  B = 85;
        break;
    }
    case 34:
    {   R = 179;  G = 146;  B = 65;
        break;
    }
    case 35:
    {   R = 1;  G = 1;  B = 1;
        break;
    }
    case 37:
    {   R = 239;  G = 239;  B = 239;
        break;
    }
    case 38:  //Dark Overall Background
    {   R = 61;  G = 61;  B = 61;
        break;
    }
    case 39:  //Light colorOverall Text
    {   R = 0;  G = 0;  B = 0;
        break;
    }
    case 40:  //Dark colorOverall Text
    {   R = 200;  G = 200;  B = 200;
        break;
    }
    case 41:  //Light color HighlightedBorders  light blue
    {   R = 135;  G = 190;  B = 193;
        break;
    }
    case 42:  //Dark color HighlightedBorders - To be defined.
    {   R = 231;  G = 231;  B = 231;
        break;
    }
    case 43:  //Light color BordersAndLines
    {   R = 0;  G = 0;  B = 0;
        break;
    }
    case 44:  //Dark color BordersAndLines
    {   R = 186;  G = 189;  B = 182;
        break;
    }
    default:
        break;
    }
    return ;
}

#endif // BUYDATAINCLUDE_H
