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

#include "keibomoneytracker.h"
#include <ctime>

inline bool Account::isCurrentYearLeap()
{
    bool leapYear = false;

    if ((Year % 4) == 0)
    {
        if ((Year % 100) == 0)
        {
            if ((Year % 400) == 0)
            {
                leapYear = true;
            }
            else
            {
                leapYear = false;
            }
        }
        else
        {
            leapYear = true;
        }
    }

    return leapYear;
}

void Account::updateDefaultGroupsToCurrentLanguage()
{    
    this->loadIncomeGroups(); //To be safe load saved groups. In case an Account has not been opened the containers will be empty.
    this->loadExpensesGroups();
    if (ACCOUNT_LANGUAGE == ENGLISH)
    {
        //Update Income groups
        for (std::vector<std::string>::iterator incomeGroupIt = IncomeGroupsNames.begin();
             incomeGroupIt != IncomeGroupsNames.end(); ++incomeGroupIt)
        {
            if ((*incomeGroupIt == "Nicht klassifiziert") || (*incomeGroupIt == "Sin clasificar"))
            {
                *incomeGroupIt = "Not classified";
            }
            else if ((*incomeGroupIt == "Gehalt") || (*incomeGroupIt == "Salario"))
            {
                *incomeGroupIt = "Salary";
            }
            else if ((*incomeGroupIt == "Verkaufen") || (*incomeGroupIt == "Ventas"))
            {
                *incomeGroupIt = "Sales";
            }
            else if ((*incomeGroupIt == "Zinsen") || (*incomeGroupIt == "Intereses"))
            {
                *incomeGroupIt = "Interests";
            }
            else if ((*incomeGroupIt == "Geschenke") || (*incomeGroupIt == "Regalos"))
            {
                *incomeGroupIt = "Gifts";
            }
        }

        //Update Expenses groups
        for (std::vector<std::string>::iterator expensesGroupIt = ExpensesGroupsNames.begin();
             expensesGroupIt != ExpensesGroupsNames.end(); ++expensesGroupIt)
        {
            if ((*expensesGroupIt == "Nicht klassifiziert") || (*expensesGroupIt == "Sin clasificar"))
            {
                *expensesGroupIt = "Not classified";
            }
            else if ((*expensesGroupIt == "Essen") || (*expensesGroupIt == "Comida"))
            {
                *expensesGroupIt = "Food";
            }
            else if ((*expensesGroupIt == "Haus") || (*expensesGroupIt == "Casa"))
            {
                *expensesGroupIt = "House";
            }
            else if ((*expensesGroupIt == "Verkehr") || (*expensesGroupIt == "Transporte"))
            {
                *expensesGroupIt = "Transportation";
            }
            else if ((*expensesGroupIt == "Geschenke") || (*expensesGroupIt == "Regalos"))
            {
                *expensesGroupIt = "Gifts";
            }
            else if ((*expensesGroupIt == "Sonstiges") || (*expensesGroupIt == "Misceláneo"))
            {
                *expensesGroupIt = "Miscellaneous";
            }
        }
    }
    else if (ACCOUNT_LANGUAGE == GERMAN)
    {
        //Update Income groups
        for (std::vector<std::string>::iterator incomeGroupIt = IncomeGroupsNames.begin();
             incomeGroupIt != IncomeGroupsNames.end(); ++incomeGroupIt)
        {
            if ((*incomeGroupIt == "Not classified") || (*incomeGroupIt == "Sin clasificar"))
            {
                *incomeGroupIt = "Nicht klassifiziert";
            }
            else if ((*incomeGroupIt == "Salary") || (*incomeGroupIt == "Salario"))
            {
                *incomeGroupIt = "Gehalt";
            }
            else if ((*incomeGroupIt == "Sales") || (*incomeGroupIt == "Ventas"))
            {
                *incomeGroupIt = "Verkaufen";
            }
            else if ((*incomeGroupIt == "Interests") || (*incomeGroupIt == "Intereses"))
            {
                *incomeGroupIt = "Zinsen";
            }
            else if ((*incomeGroupIt == "Gifts") || (*incomeGroupIt == "Regalos"))
            {
                *incomeGroupIt = "Geschenke";
            }
        }

        //Update Expenses groups
        for (std::vector<std::string>::iterator expensesGroupIt = ExpensesGroupsNames.begin();
             expensesGroupIt != ExpensesGroupsNames.end(); ++expensesGroupIt)
        {
            if ((*expensesGroupIt == "Not classified") || (*expensesGroupIt == "Sin clasificar"))
            {
                *expensesGroupIt = "Nicht klassifiziert";
            }
            else if ((*expensesGroupIt == "Food") || (*expensesGroupIt == "Comida"))
            {
                *expensesGroupIt = "Essen";
            }
            else if ((*expensesGroupIt == "House") || (*expensesGroupIt == "Casa"))
            {
                *expensesGroupIt = "Haus";
            }
            else if ((*expensesGroupIt == "Transportation") || (*expensesGroupIt == "Transporte"))
            {
                *expensesGroupIt = "Verkehr";
            }
            else if ((*expensesGroupIt == "Gifts") || (*expensesGroupIt == "Regalos"))
            {
                *expensesGroupIt = "Geschenke";
            }
            else if ((*expensesGroupIt == "Miscellaneous") || (*expensesGroupIt == "Misceláneo"))
            {
                *expensesGroupIt = "Sonstiges";
            }
        }
    }
    else if (ACCOUNT_LANGUAGE == SPANISH)
    {
        //Update Income groups
        for (std::vector<std::string>::iterator incomeGroupIt = IncomeGroupsNames.begin();
             incomeGroupIt != IncomeGroupsNames.end(); ++incomeGroupIt)
        {
            if ((*incomeGroupIt == "Not classified") || (*incomeGroupIt == "Nicht klassifiziert"))
            {
                *incomeGroupIt = "Sin clasificar";
            }
            else if ((*incomeGroupIt == "Salary") || (*incomeGroupIt == "Gehalt"))
            {
                *incomeGroupIt = "Salario";
            }
            else if ((*incomeGroupIt == "Sales") || (*incomeGroupIt == "Verkaufen"))
            {
                *incomeGroupIt = "Ventas";
            }
            else if ((*incomeGroupIt == "Interests") || (*incomeGroupIt == "Zinsen"))
            {
                *incomeGroupIt = "Intereses";
            }
            else if ((*incomeGroupIt == "Gifts") || (*incomeGroupIt == "Geschenke"))
            {
                *incomeGroupIt = "Regalos";
            }
        }

        //Update Expenses groups
        for (std::vector<std::string>::iterator expensesGroupIt = ExpensesGroupsNames.begin();
             expensesGroupIt != ExpensesGroupsNames.end(); ++expensesGroupIt)
        {
            if ((*expensesGroupIt == "Not classified") || (*expensesGroupIt == "Nicht klassifiziert"))
            {
                *expensesGroupIt = "Sin clasificar";
            }
            else if ((*expensesGroupIt == "Food") || (*expensesGroupIt == "Essen"))
            {
                *expensesGroupIt = "Comida";
            }
            else if ((*expensesGroupIt == "House") || (*expensesGroupIt == "Haus"))
            {
                *expensesGroupIt = "Casa";
            }
            else if ((*expensesGroupIt == "Transportation") || (*expensesGroupIt == "Verkehr"))
            {
                *expensesGroupIt = "Transporte";
            }
            else if ((*expensesGroupIt == "Gifts") || (*expensesGroupIt == "Geschenke"))
            {
                *expensesGroupIt = "Regalos";
            }
            else if ((*expensesGroupIt == "Miscellaneous") || (*expensesGroupIt == "Sonstiges"))
            {
                *expensesGroupIt = "Misceláneo";
            }
        }
    }

    this->saveIncomeGroups();
    this->saveExpensesGroups();
}

void Account::getGroupWithLowestIncomeInYear(std::string &groupName, double &amount)
{
    if ((this->getTotalNumberOfIncomeElements() > 0) && (IncomeGroupsAmounts.size() >1)) //Second condition ensures that loop will be iterated at least once
    {
        std::vector<double>::iterator groupAmountIt;
        double tempGroupWithLowestIncome    = 0.0;
        int    tempGroupWithLowestIncome_Id = 0;

        bool firstValidGroupFound = false;

        int analizingGroupId = 1;
            //First group is "Not Classified", ignore it ( +1 ).
        for (groupAmountIt = IncomeGroupsAmounts.begin()+1; groupAmountIt != IncomeGroupsAmounts.end(); ++groupAmountIt) //Find first group with amount > 0.0
        {
            if (!firstValidGroupFound)
            {
                if (*groupAmountIt > 0.00){
                    tempGroupWithLowestIncome    = *groupAmountIt;
                    tempGroupWithLowestIncome_Id = analizingGroupId;
                    firstValidGroupFound = true;
                }
            }
            else {
                if ((*groupAmountIt < tempGroupWithLowestIncome) && (*groupAmountIt > 0.00)){ //Find another group with less income is found and its amount > 0.0
                    tempGroupWithLowestIncome    = *groupAmountIt;
                    tempGroupWithLowestIncome_Id = analizingGroupId;
                }
            }
            ++analizingGroupId;
        }

        if (firstValidGroupFound){
            std::vector<std::string>::iterator groupNameIt = IncomeGroupsNames.begin()+tempGroupWithLowestIncome_Id;
            groupName = *(groupNameIt);
            amount    = tempGroupWithLowestIncome;
        } else if (!firstValidGroupFound){
            groupName = "N/A";
            amount = 0.0;
        }
    }
    else {
        groupName = "N/A";
        amount = 0.0;
    }
}

void Account::getGroupWithLowestExpensesInYear(std::string &groupName, double &amount)
{
    if ((this->getTotalNumberOfExpensesElements() > 0) && (ExpensesGroupsAmounts.size() > 1)) //Second condition ensures that loop will be iterated at least once
    {
        std::vector<double>::iterator groupAmountIt;
        double tempGroupWithLowestExpenses    = 0.0;
        int    tempGroupWithLowestExpenses_Id = 0;

        bool firstValidGroupFound = false;

        int analizingGroupId = 1;
            //First group is "Not Classified", ignore it ( +1 ).
        for (groupAmountIt = ExpensesGroupsAmounts.begin()+1; groupAmountIt != ExpensesGroupsAmounts.end(); ++groupAmountIt) //Find first group with amount > 0.0
        {
            if (!firstValidGroupFound)
            {
                if (*groupAmountIt > 0.00){
                    tempGroupWithLowestExpenses    = *groupAmountIt;
                    tempGroupWithLowestExpenses_Id = analizingGroupId;
                    firstValidGroupFound = true;
                }
            }
            else {
                if ((*groupAmountIt < tempGroupWithLowestExpenses) && (*groupAmountIt > 0.00)){ //Find another group with less income is found and its amount > 0.0
                    tempGroupWithLowestExpenses    = *groupAmountIt;
                    tempGroupWithLowestExpenses_Id = analizingGroupId;
                }
            }
            ++analizingGroupId;
        }

        if (firstValidGroupFound){
            std::vector<std::string>::iterator groupNameIt = ExpensesGroupsNames.begin()+tempGroupWithLowestExpenses_Id;
            groupName = *(groupNameIt);
            amount    = tempGroupWithLowestExpenses;
        } else if (!firstValidGroupFound){
            groupName = "N/A";
            amount = 0.0;
        }
    }
    else {
        groupName = "N/A";
        amount = 0.0;
    }
}

void Account::getGroupWithHighestIncomeInYear(std::string &groupName, double &amount)
{
    if ((this->getTotalNumberOfIncomeElements() > 0) && (IncomeGroupsAmounts.size() > 1)) //First group is "Not Classified", ignore it.
    {
        std::vector<double>::iterator groupAmountIt = IncomeGroupsAmounts.begin()+1; //Set first group as highest
        double tempHighestIncome = *groupAmountIt;
        int    tempGroupId       = 1;

        int analizingGroupId = 2;
        for (groupAmountIt = IncomeGroupsAmounts.begin()+2; groupAmountIt != IncomeGroupsAmounts.end(); ++groupAmountIt) //Ignore first two groups (Not classified and first existing group).
        {                                                                                                                //If there exist only one group (E.g.: "Salary") the iterator groupAmountIt
            if (*groupAmountIt > tempHighestIncome){                                                                     //will point directly to IncomeGroupsAmounts.end() and nothing will be done.
                tempHighestIncome = *groupAmountIt;
                tempGroupId       = analizingGroupId;
            }
            ++analizingGroupId;
        }

        if (tempHighestIncome > 0.00){
            std::vector<std::string>::iterator groupNameIt = IncomeGroupsNames.begin()+tempGroupId;
            groupName = *(groupNameIt);
            amount    = tempHighestIncome;
        } else {
            groupName = "N/A";
            amount = 0.0;
        }

    }
    else {
        groupName = "N/A";
        amount = 0.0;
    }
}

void Account::getGroupWithHighestExpensesInYear(std::string &groupName, double &amount)
{
    if ((this->getTotalNumberOfExpensesElements() > 0) && (ExpensesGroupsAmounts.size() > 1)) //First group is "Not Classified", ignore it.
    {
        std::vector<double>::iterator groupExpensesIt = ExpensesGroupsAmounts.begin()+1; //Set first group as highest
        double tempHighestIncome = *groupExpensesIt;
        int    tempGroupId       = 1;

        int analizingGroupId = 2;
        for (groupExpensesIt = ExpensesGroupsAmounts.begin()+2; groupExpensesIt != ExpensesGroupsAmounts.end(); ++groupExpensesIt) //Ignore first two groups (Not classified and first existing group)
        {
            if (*groupExpensesIt > tempHighestIncome){
                tempHighestIncome = *groupExpensesIt;
                tempGroupId       = analizingGroupId;
            }
            ++analizingGroupId;
        }

        if (tempHighestIncome > 0.00){
            std::vector<std::string>::iterator groupNameIt = ExpensesGroupsNames.begin()+tempGroupId;
            groupName = *(groupNameIt);
            amount    = tempHighestIncome;
        } else {
            groupName = "N/A";
            amount = 0.0;
        }

    }
    else {
        groupName = "N/A";
        amount = 0.0;
    }
}

void Account::getLowestMonthlyIncomeInYear(double &amount, int &month)
{
    if (this->getTotalNumberOfIncomeElements() > 0)
    {
        double tempAmount = 0.0;
        int tempMonth = 0;

        int firstValidMonth = 0;

        for (int month = 0; month != 12; ++month) //Find first month with an income and assign it as lowest
        {
            if (getIncomeInMonth(month) > 0.0){
                tempAmount = getIncomeInMonth(month);
                tempMonth = month;
                firstValidMonth  = month;
                break;
            }
        }

        for (int month = firstValidMonth; month != 12; ++month) //Compare it to the rest, assign one as lowest if the case
        {
            if ((getIncomeInMonth(month) < tempAmount) && (getIncomeInMonth(month) > 0.0)) {
                tempAmount = getIncomeInMonth(month);
                tempMonth  = month;
            }
        }
        amount = tempAmount;
        month  = tempMonth;
    }
}

void Account::getLowestMonthlyExpensesInYear(double &amount, int &month)
{
    if (this->getTotalNumberOfExpensesElements() > 0)
    {
        double tempAmount = 0.0;
        int tempMonth = 0;
        int firstValidMonth = 0;

        for (int month = 0; month != 12; ++month) //Find first month with expenses and assign it as lowest
        {
            if (getExpensesInMonth(month) > 0.0){
                tempAmount = getExpensesInMonth(month);
                tempMonth = month;
                firstValidMonth  = month;
                break;
            }
        }

        for (int month = firstValidMonth; month != 12; ++month)
        {
            if ((getExpensesInMonth(month) < tempAmount) && (getExpensesInMonth(month) > 0.0)){
                tempAmount = getExpensesInMonth(month);
                tempMonth  = month;
            }
        }
        amount = tempAmount;
        month  = tempMonth;
    }
}

void Account::getHighestMonthlyIncomeInYear(double &amount, int &month)
{
    if (this->getTotalNumberOfIncomeElements() > 0)
    {
        double tempAmount = getIncomeInMonth(0);  //Assign first month as highest
        int tempMonth = 0;
        for (int month = 1; month != 12; ++month)
        {
            if (tempAmount < getIncomeInMonth(month)){
                tempAmount = getIncomeInMonth(month);
                tempMonth  = month;
            }
        }
        amount = tempAmount;
        month  = tempMonth;
    }
}

void Account::getHighestMonthlyExpensesInYear(double &amount, int &month)
{
    if (this->getTotalNumberOfExpensesElements() > 0)
    {
        double tempAmount =  getExpensesInMonth(0); //Assign first month as highest
        int tempMonth = 0;
        for (int month = 1; month != 12; ++month)
        {
            if (tempAmount < getExpensesInMonth(month)){
                tempAmount = getExpensesInMonth(month);
                tempMonth  = month;
            }
        }
        amount = tempAmount;
        month  = tempMonth;
    }
}

void Account::getHighestIncomeInYear_Transaction(Transaction &highestIncomeInYear)
{
    if (this->getTotalNumberOfIncomeElements() > 0)
    {
        Transaction *tempArticle;
        double highestIncome = 0.0;
        bool newValueWasAssigned = false;

        for (unsigned short int month = 0; month != 12; ++month)
        {
            std::vector<Transaction>::iterator articleIt;
            for (articleIt = Yearly_Articles[month].begin(); articleIt != Yearly_Articles[month].end(); ++articleIt)
            {
                if (articleIt->IsIncome && (articleIt->Amount > highestIncome) ){
                    highestIncome = articleIt->Amount;
                    tempArticle=&(*articleIt);
                    newValueWasAssigned = true;
                }
            }
        }
        if (newValueWasAssigned){
            highestIncomeInYear = *tempArticle;
        }
    }
}

void Account::getHighestExpenseInYear_Transaction(Transaction &highestExpenseInYear)
{
    if (this->getTotalNumberOfExpensesElements() > 0)
    {
        Transaction *tempArticle;
        double highestExpense = 0.0;
        bool newValueWasAssigned = false;

        for (unsigned short int month = 0; month != 12; ++month)
        {
            std::vector<Transaction>::iterator articleIt;
            for (articleIt = Yearly_Articles[month].begin(); articleIt != Yearly_Articles[month].end(); ++articleIt)
            {
                if ((!articleIt->IsIncome) && (articleIt->Amount > highestExpense) && (articleIt->Amount > 0.00)){
                    highestExpense = articleIt->Amount;
                    tempArticle=&(*articleIt);
                    newValueWasAssigned = true;
                }
            }
        }
        if (newValueWasAssigned){
            highestExpenseInYear = *tempArticle;
        }
    }
}

void Account::getFirstElement(Transaction &firstElement)
{
    if (this->getTotalNumberOfElements() > 0)
    {
        for (unsigned short int month = 0; month != 12; ++month)
        {
            std::vector<Transaction>::iterator articleIt;
            for (articleIt = Yearly_Articles[month].begin(); articleIt != Yearly_Articles[month].end(); ++articleIt)
            {
                firstElement = *articleIt; //First element found
                return;
            }
        }
    }
}

void Account::getLastElement(Transaction &lastElement)
{
    if (this->getTotalNumberOfElements() > 0)
    {
        Transaction tempArticle;
        for (unsigned short int month = 0; month != 12; ++month)
        {
            std::vector<Transaction>::iterator articleIt;
            for (articleIt = Yearly_Articles[month].begin(); articleIt != Yearly_Articles[month].end(); ++articleIt)
            {
                tempArticle = *articleIt; //Current element made last
            }
        }
        lastElement = tempArticle;
        return;
    }
}

std::string Account::getAccountLanguageString()
{
    switch (ACCOUNT_LANGUAGE) {
    case ENGLISH:
        return "English";
    case SPANISH:
        return "Español";
    case GERMAN:
        return "Deutsch";
    default:
        break;
    }

    return "No Language Selected";
}

std::string Account::getAccountCurrencyString()
{
        switch (ACCOUNT_CURRENCY) {
        case DOLLAR:
            return "$ - Dollar";
        case EURO:
            return "€ - Euro";
        case FRANC:
            return "Fr. - Franc";
        case PESO:
            return "$ - Peso";
        case YEN:
            return "¥ - Yen";
        case POUND:
            return "£ - Pound";
        case RUBLE:
            return "₽ - Ruble";
        case KRONE:
            return "kr - Krone";
        case RUPEE:
            return "₹ - Rupee";
        case NEWSHECKEL:
            return "₪ - New Shekel";
        case RAND:
            return "R - Rand";
        case ZLOTY:
            return "zł - Złoty";
        case YUAN:
            return "¥ - Yuan";
        case REAL:
            return "R$ - Real";
        case KUNA:
            return "kn - Kuna";
        case LIRA:
            return "₺ - Lira";
        case MANAT:
            return "₼ - Manat";
        case SOL:
            return "S/. - Sol";
        case RUBLE_BELARUS:
            return "Br - Ruble";
        case NAIRA:
            return "₦ - Naira";
        case KRONA:
            return "kr - Krona";
        case RIYAL:
            return "QR- Riyal";
        case KORUNA:
            return "Kč - Koruna";
        case WON:
            return "₩ - Won";
        default:
            break;
        }

    return "No Currency Selected";
}

std::vector<std::string> Account::getCurrencyList() //The order in which currencies are added in this function matters, it has to be the same as the order sequence in "enum Currency"
{
    std::vector<std::string> tempList;
    tempList.push_back("$ - Dollar");
    tempList.push_back("€ - Euro");
    tempList.push_back("Fr. - Franc");
    tempList.push_back("Kč - Koruna");
    tempList.push_back("kn - Kuna");
    tempList.push_back("kr - Krona");
    tempList.push_back("kr - Krone");
    tempList.push_back("₺ - Lira");
    tempList.push_back("₼ - Manat");
    tempList.push_back("₦ - Naira");
    tempList.push_back("₪ - New Shekel");
    tempList.push_back("$ - Peso");
    tempList.push_back("£ - Pound");
    tempList.push_back("R - Rand");
    tempList.push_back("R$ - Real");
    tempList.push_back("QR- Riyal");
    tempList.push_back("₽ - Ruble");
    tempList.push_back("Br - Ruble");
    tempList.push_back("₹ - Rupee");
    tempList.push_back("S/. - Sol");
    tempList.push_back("₩ - Won");
    tempList.push_back("¥ - Yen");
    tempList.push_back("¥ - Yuan");
    tempList.push_back("zł - Złoty");

    return tempList;
}

std::string Account::getAccountCurrencySymbol()
{
    return getCurrenySymbol(ACCOUNT_CURRENCY);
}

double Account::getBalanceInYear()
{
    return (this->getTotalIncomeInYear()-this->getTotalExpensesInYear());
}

double Account::getBalanceInMonth(const int &mon)
{
    return (this->getIncomeInMonth(mon)-this->getExpensesInMonth(mon));
}

Account::Account(const int &year)
{
    Year = year;
    customColorConfiguration.colorThemeName = "Custom";
    //std::cout<<"CUSTOM COLOR CONFIGURATION COLORBARINCOMESELECTED"<<customColorConfiguration.colorBarIncomeSelected<<'\n';
}

void Account::setAccountCurrentColorTheme(unsigned int theme)
{
    ACCOUNT_CURRENT_COLOR_THEME = theme;
}

bool Account::hasProfileImage()
{
    std::string noImage = "No Image Selected";
    //if (ACCOUNT_ICON_PATH_NAME.empty())
    if (ACCOUNT_ICON_PATH_NAME == noImage)
    {
        return false;
    } else {
        return true;
    }
    return false;
}

std::vector<std::string> Account::getLanguageList()
{
    std::vector<std::string> tempList;
    tempList.push_back("English");
    tempList.push_back("Deutsch");
    tempList.push_back("Español");

    return tempList;
}

bool Account::loadAccountProperties(std::string accountName, std::string accountFolderPath)
{
    std::cout<<"ACCOUNT FOLDER PATH GIVEN BY MANAGER: "<<accountFolderPath<<'\n';
    //Check if file Properties already exists, if not return false
    std::ifstream propertiesFile;
    propertiesFile.open(accountFolderPath+"/Properties.txt");
    if (!propertiesFile.is_open())
    {
        std::cout<<"NO PROPERTIES FILE FOUND FOR THIS ACCOUNT"<<'\n';
        PropertyFileExists = false;
        return false;
    }

    const short int TOTAL_NUMBER_OF_PROPERTIES = 6;
    bool propertiesOk = true;               //Checks properties values.
    bool allPropertiesExist[TOTAL_NUMBER_OF_PROPERTIES] = {false};      //Checks that no property is missing in file.
    std::string line;
    int numberOfLine = 0;
    while(std::getline(propertiesFile, line))
    {
        if (!line.empty())
        {
            short int xEnum = 0;

            //GET PROPERTY NAME
            std::string propertyName;
            bool addCharacterToPropertyName = true;
            int whiteSpaces = 0;
            for (std::string::iterator it = line.begin(); it != line.end(); ++it)
              {
                if ((*it == ':') || (*it == '=')){
                    addCharacterToPropertyName = false;
                    //std::cout<<"Property name gotten"<<'\n';
                }
                else if (*it == ' ') {
                    ++whiteSpaces; //Detect whitespaces to create Offset to property value
                    //std::cout<<"WhiteSpace gotten"<<'\n';
                    continue;
                }
                else if (*it != ' ') {
                    if (!addCharacterToPropertyName) {/*std::cout<<"Value of property reached"<<'\n';*/ break;}
                }

                if (addCharacterToPropertyName){
                    propertyName += *it;
                    //std::cout<<"Character to property name added: "<<*it<<'\n';
                }
            }

            //DEPENDING ON PROPERTY NAME GET PROPERTY VALUE AND VERIFY THAT IT HAS AN ACCEPTABLE VALUE
            if (propertyName == "Name"){
                std::string tempAccountName;
                allPropertiesExist[0] = true;
                for (std::string::iterator it = line.begin()+(propertyName.size()+whiteSpaces+1); it != line.end(); ++it)
                  {
                        tempAccountName += *it;
                }
                if (tempAccountName == accountName){
                    ACCOUNT_NAME = tempAccountName;
                    std::cout<<"ACCOUNT NAME READ: "<<ACCOUNT_NAME<<'\n';
                } else {
                    propertiesOk = false;
                    std::cout<<"WRONG/NO ACCOUNT NAME "<<'\n';
                }
            }
            else if (propertyName == "Path") {
                std::string tempAccountPath;
                allPropertiesExist[1] = true;
                for (std::string::iterator it = line.begin()+(propertyName.size()+whiteSpaces+1); it != line.end(); ++it)
                  {
                        tempAccountPath += *it;
                }
                if (tempAccountPath == accountFolderPath){
                    ACCOUNT_FOLDER_PATH = tempAccountPath;
                    ACCOUNT_ICON_PATH_NAME = tempAccountPath+"/AccountIcon.png";
                    std::cout<<"ACCOUNT PATH OK: "<<tempAccountPath<<'\n';
                } else {
                    //propertiesOk = false;
                    ACCOUNT_FOLDER_PATH = accountFolderPath;
                    ACCOUNT_ICON_PATH_NAME = accountFolderPath+"/AccountIcon.png";
                    std::cout<<" PATH IS DIFFERENT, MAYBE ACCOUNT IS ACCESSED ON A DIFFERENT COMPUTER "<<'\n';
                }
            }
            else if (propertyName == "Language") {
                std::string tempAccountLanguage;
                allPropertiesExist[2] = true;
                for (std::string::iterator it = line.begin()+(propertyName.size()+whiteSpaces+1); it != line.end(); ++it)
                  {
                        tempAccountLanguage += *it;
                }
                std::stringstream ss1(tempAccountLanguage);
                                ss1>>xEnum;
                if (xEnum > -1 && xEnum < 5){
                    ACCOUNT_LANGUAGE = static_cast<Language>(xEnum);
                    std::cout<<"ACCOUNT LANGUAGE READ: "<<tempAccountLanguage<<'\n';
                } else {
                    propertiesOk = false;
                    std::cout<<" WRONG ACCOUNT LANGUAGE "<<'\n';
                }
            }
            else if (propertyName == "Currency") {
                std::string tempAccountCurrency;
                allPropertiesExist[3] = true;
                for (std::string::iterator it = line.begin()+(propertyName.size()+whiteSpaces+1); it != line.end(); ++it)
                  {
                        tempAccountCurrency += *it;
                }
                std::stringstream ss2(tempAccountCurrency);
                                ss2>>xEnum;
                if (xEnum > -1 && xEnum < NUMBER_OF_CURRENCIES){
                    ACCOUNT_CURRENCY = static_cast<Currency>(xEnum);
                    std::cout<<"ACCOUNT CURRENCY READ: "<<tempAccountCurrency<<'\n';
                } else {
                    propertiesOk = false;
                    std::cout<<" WRONG ACCOUNT CURRENCY "<<'\n';
                }
            }
            else if (propertyName == "ColorTheme") {
                std::string tempAccountColorTheme;
                allPropertiesExist[4] = true;
                for (std::string::iterator it = line.begin()+(propertyName.size()+whiteSpaces+1); it != line.end(); ++it)
                  {
                        tempAccountColorTheme += *it;
                }
                std::stringstream ss3(tempAccountColorTheme);
                                ss3>>xEnum;
                if (xEnum > -1 && xEnum < NUMBER_OF_MAX_CONFIGURATIONS){
                    ACCOUNT_CURRENT_COLOR_THEME = xEnum;
                    std::cout<<"ACCOUNT COLORTHEME READ: "<<tempAccountColorTheme<<'\n';
                } else {
                    propertiesOk = false;
                    std::cout<<" WRONG ACCOUNT COLOR THEME "<<'\n';
                }
            }
            else if (propertyName == "CustomColor") {
                std::string tempAccountCustomColors;
                allPropertiesExist[5] = true;
                for (std::string::iterator it = line.begin()+(propertyName.size()+whiteSpaces+1); it != line.end(); ++it)
                  {
                        tempAccountCustomColors += *it;
                }
                std::stringstream ss4(tempAccountCustomColors);
                ss4>> customColorConfiguration.colorBarIncomeSelected>>
                      customColorConfiguration.colorBarIncomeUnselected>>
                      customColorConfiguration.colorBarExpensesSelected>>
                      customColorConfiguration.colorBarExpensesUnselected>>
                      customColorConfiguration.colorBarBackground>>
                      customColorConfiguration.colorGroupIncomeSelected>>
                      customColorConfiguration.colorGroupIncomeUnselected>>
                      customColorConfiguration.colorGroupExpensesSelected>>
                      customColorConfiguration.colorGroupExpensesUnselected>>
                      customColorConfiguration.colorGroupIncomeBackground>>
                      customColorConfiguration.colorGroupExpensesBackground>>
                      customColorConfiguration.colorTableIncomeAmount>>
                      customColorConfiguration.showMonthlyAmountsInColor>> //this is a bool and it will not be checked
                      customColorConfiguration.useDarkOverallTheme;   //this is a bool and it will not be checked

                //In this case, if no valid values are found set default values and inform user that properties were changed.
                if ((customColorConfiguration.colorBarIncomeSelected<0) || (customColorConfiguration.colorBarIncomeSelected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorBarIncomeSelected=13; propertiesOk=false; std::cout<<"WRONG colorBarIncomeSelected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorBarIncomeUnselected<0) || (customColorConfiguration.colorBarIncomeUnselected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorBarIncomeUnselected=4; propertiesOk=false; std::cout<<"WRONG colorBarIncomeUnselected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorBarExpensesSelected<0) || (customColorConfiguration.colorBarExpensesSelected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorBarExpensesSelected=9; propertiesOk=false; std::cout<<"WRONG colorBarExpensesSelected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorBarExpensesUnselected<0) || (customColorConfiguration.colorBarExpensesUnselected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorBarExpensesUnselected=7; propertiesOk=false; std::cout<<"WRONG colorBarExpensesUnselected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorBarBackground<0) || (customColorConfiguration.colorBarBackground>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorBarBackground=36; propertiesOk=false; std::cout<<"WRONG colorBarBackground IN FILE"<<'\n';}
                if ((customColorConfiguration.colorGroupIncomeSelected<0) || (customColorConfiguration.colorGroupIncomeSelected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorGroupIncomeSelected=13; propertiesOk=false; std::cout<<"WRONG colorGroupIncomeSelected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorGroupIncomeUnselected<0) || (customColorConfiguration.colorGroupIncomeUnselected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorGroupIncomeUnselected=4; propertiesOk=false; std::cout<<"WRONG colorGroupIncomeUnselected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorGroupExpensesSelected<0) || (customColorConfiguration.colorGroupExpensesSelected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorGroupExpensesSelected=9; propertiesOk=false; std::cout<<"WRONG colorGroupExpensesSelected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorGroupExpensesUnselected<0) || (customColorConfiguration.colorGroupExpensesUnselected>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorGroupExpensesUnselected=16; propertiesOk=false; std::cout<<"WRONG colorGroupExpensesUnselected IN FILE"<<'\n';}
                if ((customColorConfiguration.colorGroupIncomeBackground<0) || (customColorConfiguration.colorGroupIncomeBackground>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorGroupIncomeBackground=7; propertiesOk=false; std::cout<<"WRONG colorGroupIncomeBackground IN FILE"<<'\n';}
                if ((customColorConfiguration.colorGroupExpensesBackground<0) || (customColorConfiguration.colorGroupExpensesBackground>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorGroupExpensesBackground=7; propertiesOk=false; std::cout<<"WRONG colorGroupExpensesBackground IN FILE"<<'\n';}
                if ((customColorConfiguration.colorTableIncomeAmount<0) || (customColorConfiguration.colorTableIncomeAmount>NUMBER_OF_POSSIBLE_COLORS)){customColorConfiguration.colorTableIncomeAmount=13; propertiesOk=false; std::cout<<"WRONG colorTableIncomeAmount IN FILE"<<'\n';}

                std::cout<<"ACCOUNT CUSTOMCOLOR READ: "<<tempAccountCustomColors<<'\n';
                customColorConfiguration.setOverallThemeColors();
            }
            else {
                if (numberOfLine > 0){
                    propertiesOk = false;
                std::cout<<"UNKNOWN PROPERTY NAME IN LINE "<<numberOfLine<<'\n';
                }
            }
        }
        ++numberOfLine;
    }
    propertiesFile.close();
    std::cout<<"PROPERTIES FROM FILE RETRIEVED"<<'\n'<<'\n';

    for (unsigned int i = 0; i != TOTAL_NUMBER_OF_PROPERTIES; ++i){ //If any property is missing return false
        if (allPropertiesExist[i] == false) {
            return false;
        }
    }

    return propertiesOk;
}

void Account::saveAccountProperties()
{
    std::string Header = "DO NOT EDIT - NO EDITAR - NICHT ÄNDERN - 編集しないでください。- NE PAS MODIFIER";
    std::ofstream propertiesFile;
    propertiesFile.open(ACCOUNT_FOLDER_PATH+"/Properties.txt");
    propertiesFile<<Header<<'\n'
                 <<"Name: "<<ACCOUNT_NAME<<'\n'
                <<"Path: "<<ACCOUNT_FOLDER_PATH<<'\n'
             <<"Language: "<<ACCOUNT_LANGUAGE<<'\n'
            <<"Currency: "<<ACCOUNT_CURRENCY<<'\n'
           <<"ColorTheme: "<<ACCOUNT_CURRENT_COLOR_THEME<<'\n'
          <<"CustomColor: "<<customColorConfiguration.colorBarIncomeSelected<<" "
            <<customColorConfiguration.colorBarIncomeUnselected<<" "
            <<customColorConfiguration.colorBarExpensesSelected<<" "
            <<customColorConfiguration.colorBarExpensesUnselected<<" "
            <<customColorConfiguration.colorBarBackground<<" "
            <<customColorConfiguration.colorGroupIncomeSelected<<" "
            <<customColorConfiguration.colorGroupIncomeUnselected<<" "
            <<customColorConfiguration.colorGroupExpensesSelected<<" "
            <<customColorConfiguration.colorGroupExpensesUnselected<<" "
            <<customColorConfiguration.colorGroupIncomeBackground<<" "
            <<customColorConfiguration.colorGroupExpensesBackground<<" "
            <<customColorConfiguration.colorTableIncomeAmount<<" "
            <<customColorConfiguration.showMonthlyAmountsInColor<<" "
            <<customColorConfiguration.useDarkOverallTheme;

    propertiesFile.close();
    PropertyFileExists = true;
}

int Account::addTransaction(Transaction &temp_Article)
{
    ////Add new articles to the corresponding month
    Yearly_Articles[temp_Article.Month].push_back(temp_Article);

    if (temp_Article.IsIncome)
    {
        Total_Income += temp_Article.Amount;
        ++totalNumberOfIncomeElements;

        std::vector<double>::iterator it1 = IncomeGroupsAmounts.begin();
        *(it1+temp_Article.Group) += temp_Article.Amount;
    }

    else if (!temp_Article.IsIncome)
    {
        ///Increase total expenditures and total number of articles
        Total_Expenses+=temp_Article.Amount;
        ++totalNumberOfExpensesElements;

        ///Update global category expenditures
        //Categories_Expenditures[temp_Article.Group] += temp_Article.Amount;
        std::vector<double>::iterator it = ExpensesGroupsAmounts.begin();
        *(it+temp_Article.Group) += temp_Article.Amount;
    }
    ++NumberOfTransactions;

    return NumberOfTransactions;
}

int Account::deleteMultipleTransactionsInMonth(const int &mon, std::vector<int> listOfItemsToDelete)
{
    int offset = 1;
    //IF LIST OF ELEMENTS TO DELETE PROVIDED (FROM SELECTED ELEMENTS IN LIST) IS NOT ARRANGED ACCORDING TO ELEMENTS IN VECTOR, ARRANGE THEM!
    for (std::vector<int>::iterator startFrom = listOfItemsToDelete.begin(); startFrom != listOfItemsToDelete.end()-1; startFrom++)
    {
        //std::cout<<"START FROM= "<<*startFrom<<'\n';
        for (std::vector<int>::iterator x = listOfItemsToDelete.begin()+offset; x != listOfItemsToDelete.end(); ++x) {
            if (*x < *startFrom ){
                int buffer = *startFrom;
                //std::cout<<"Smaller number found values are going to be swaped "<<*x<<'\n';
                *startFrom = *x;
                *x = buffer;
            }
        }
        ++offset;
    }
    /*for (unsigned int i = 0; i != listOfItemsToDelete.size(); ++i){
        std::cout<<"ARRANGED ELEMENTS: "<<listOfItemsToDelete[i]<<'\n';
        }*/

    std::vector<std::vector<Transaction>>::iterator monthIterator = Yearly_Articles.begin()+mon;
    std::vector<Transaction>::iterator it = (*monthIterator).begin();

    offset = 0;
    for (std::vector<int>::iterator idOfItemToDelete = listOfItemsToDelete.begin();
         idOfItemToDelete != listOfItemsToDelete.end(); ++idOfItemToDelete) {

        if ((it + (*idOfItemToDelete) - offset)->IsIncome)
        {
            ///Decrease total income
            Total_Income-=((it + (*idOfItemToDelete) - offset)->Amount);
            ///Decrease total income for the specific group
            std::vector<double>::iterator it2 = IncomeGroupsAmounts.begin();
            *(it2+((it + (*idOfItemToDelete) - offset)->Group)) -= (it + (*idOfItemToDelete) - offset)->Amount;
            ///Substract 1 to the number of income elements
            --totalNumberOfIncomeElements;
        }
        else if ((it + (*idOfItemToDelete) - offset)->IsIncome == false)
        {
            ///Decrease total expenses
            Total_Expenses-=((it + (*idOfItemToDelete) - offset)->Amount);
            ///Decrease total expenses for the specific group
            std::vector<double>::iterator it2 = ExpensesGroupsAmounts.begin();
            *(it2+((it + (*idOfItemToDelete) - offset)->Group)) -= (it + (*idOfItemToDelete) - offset)->Amount;
            ///Substract 1 to the number of expenses elements
            --totalNumberOfExpensesElements;
        }

        --NumberOfTransactions;

        ///Erase element at a given month
        //std::cout<<"BEFORE ERASE"<<'\n';
        Yearly_Articles[mon].erase((it + (*idOfItemToDelete) - offset));
        //std::cout<<"AFTER ERASE"<<'\n';
        ++offset;
    }

    return NumberOfTransactions;
}

double Account::getExpensesInMonth(const int &mon)
{
    double Monthly_Expenditures = 0.0;
    for (std::vector<Transaction>::iterator it = Yearly_Articles[mon].begin(); it != Yearly_Articles[mon].end(); ++it)
    {
        if (!(it->IsIncome)){
        Monthly_Expenditures += (it->Amount);  //Iterate through all elements of a given month
        }
    }
    return Monthly_Expenditures;
}

double Account::getIncomeInMonth(const int &mon)
{
    double MonthlyIncome = 0.0;
    for (std::vector<Transaction>::iterator it = Yearly_Articles[mon].begin(); it != Yearly_Articles[mon].end(); ++it)
    {
        if (it->IsIncome){
            MonthlyIncome += (it->Amount);
        }
    }
    return MonthlyIncome;
}

void Account::deleteSingleTransaction(int month, int id)
{
    std::vector<Transaction>::iterator currentTransactionIterator = Yearly_Articles[month].begin()+id;
    if (currentTransactionIterator->IsIncome)
    {
        Total_Income -= currentTransactionIterator->Amount;
        std::vector<double>::iterator it1 = IncomeGroupsAmounts.begin();
        *(it1+currentTransactionIterator->Group) -= currentTransactionIterator->Amount;
        ///Substract 1 to the number of income elements
        --totalNumberOfIncomeElements;
    }
    else if (!(currentTransactionIterator->IsIncome))
    {
        ///Increase total expenditures and total number of articles
        Total_Expenses-=currentTransactionIterator->Amount;
        ///Update global category expenses
        std::vector<double>::iterator it = ExpensesGroupsAmounts.begin();
        *(it+currentTransactionIterator->Group) -= currentTransactionIterator->Amount;
        ///Substract 1 to the number of expenses elements
        --totalNumberOfExpensesElements;
    }
    --NumberOfTransactions;
    Yearly_Articles[month].erase(currentTransactionIterator);
}

void Account::sortTransactionsByDate()
{
    for (int month = 0; month != 12; ++month)
    {
        const int numberOfArticles = Yearly_Articles[month].size();

        if (numberOfArticles > 1)
        {
            for (int currentTransaction = 0; currentTransaction != numberOfArticles-1; ++currentTransaction)
            {
               std::vector<Transaction>::iterator currentTransactionIterator = Yearly_Articles[month].begin()+currentTransaction;
               std::vector<Transaction>::iterator nextTransactionIterator = currentTransactionIterator+1;

                if ((currentTransactionIterator->Day) > nextTransactionIterator->Day){
                 //std::cout<<"TRANSACTION WITH LATER DAY THAN NEXT FOUND IN MONTH: "<<month<<" "<<'\n'<<currentTransactionIterator->give_Name()<<" "<<"LATER THAN "<<nextTransactionIterator->give_Name()<<'\n';

                   Transaction tempTransaction = *currentTransactionIterator;
                   currentTransaction = 0;

                   if (currentTransactionIterator->IsIncome)
                   {
                       Total_Income -= currentTransactionIterator->Amount;
                       std::vector<double>::iterator it1 = IncomeGroupsAmounts.begin();
                       *(it1+currentTransactionIterator->Group) -= currentTransactionIterator->Amount;
                   }
                   else if (!(currentTransactionIterator->IsIncome))
                   {
                       ///Increase total expenses and total number of articles
                       Total_Expenses-=currentTransactionIterator->Amount;
                       ///Update global category expenditures
                       std::vector<double>::iterator it = ExpensesGroupsAmounts.begin();
                       *(it+currentTransactionIterator->Group) -= currentTransactionIterator->Amount;
                   }
                   --NumberOfTransactions;
                   Yearly_Articles[month].erase(currentTransactionIterator);

                   this->addTransaction(tempTransaction);
                   //std::cout<<"TRANSACTION MOVED TO LAST"<<'\n'<<'\n';
                }
            }
        }
    }
}

bool Account::load_Data()
{
     std::ifstream loaddata_File;
     loaddata_File.open(ACCOUNT_FOLDER_PATH+"/data_"+std::to_string(this->Year)+".txt");
     listOfFaultyTransactionsInfo.clear();

     if (!loaddata_File)
     {
         //std::cout<<"No data file for year "<<std::to_string(this->Year)<<" was found"<<'\n';
         return false;
     }

     allTransactionsOk=true;
     std::string line;
     int previousMonth = 0;
     int previousDay = 1;

     while (std::getline(loaddata_File, line))
     {
         //std::cout<<"LINE GOTTEN: "<<line<<'\n';
         if (!line.empty())
            {
             double     price  = 0;
             int        month  = 0;
             int        day    = 0;
             int        categ  = 0;
             bool       income = false;
             int        repeat = 0;
             std::string name;

             /////Read each character on line until 6 elements are detected to recognize name of article
             std::string tempName  = "";
             int numberOfPassedElements = 0;
             bool anElementsValueIsBeingProcessed = false;

             for (std::string::iterator it = line.begin(); it != line.end(); ++it)
             {
                if ( (numberOfPassedElements <= 6) && ((*it == ' ')||(*it == '\t')) ) {
                     //std::cout<<"WhiteSpace gotten"<<'\n';
                     anElementsValueIsBeingProcessed = false;
                 }
                else if ( (numberOfPassedElements <= 6) && ((*it != ' ')||(*it != '\t')) ) {
                     if (!anElementsValueIsBeingProcessed){
                         ++numberOfPassedElements;
                         //std::cout<<"Number of passed elements(not the same as the id element) "<<numberOfPassedElements<<'\n';
                     }
                     anElementsValueIsBeingProcessed = true;
                 }

                if (numberOfPassedElements > 6){
                   // std::cout<<"Current element added: "<<*it<<" ";
                    tempName += *it;
                }
             }
            //std::cout<<'\n'<<"TRANSACTION NAME GOTTEN: " <<tempName<<" - ";
             name = tempName;

              std::stringstream ss(line);
              ss>>price;
              ss>>month;
              ss>>day;
              ss>>income;
              ss>>categ;
              ss>>repeat;

                  //Check validity of values
                  bool transactionOK = true;
                  bool nameOK  = true;
                  bool priceOK = true;
                  bool monthOK = true;
                  bool dayOK   = true;
                  bool incomeGroupOK = true;
                  bool expenseGroupOK = true;
                  bool repeatOK = true;

                  if ( name.empty() ) {nameOK=false;}
                  if ( price < 0.0 ) {priceOK=false;}
                  if ( (month<Months::JANUARY) || (month>Months::DECEMBER ) ) { monthOK=false; }
                  if ( (day<1)   || (day>31) ){ dayOK=false;}
                  if (income) {
                      if ( (categ<0) || (categ>=(static_cast<int>(IncomeGroupsNames.size())) ) ) { incomeGroupOK=false;}
                  } else if (!income) {
                      if ( (categ<0) || (categ>=(static_cast<int>(ExpensesGroupsNames.size())) ) ) {expenseGroupOK=false;}
                  }
                  if (repeat <0 || repeat > 3) {repeatOK = false;}

                  if (!nameOK) {
                      name="Unknown";
                      transactionOK = false;
                      std::cout<<"WRONG name TRANSACTION FOUND"<<'\n';
                  }
                  if (!priceOK) {
                      price=0.0;
                      transactionOK = false;
                      std::cout<<"WRONG amount TRANSACTION FOUND"<<'\n';
                  }
                  if (!monthOK) {
                      month = previousMonth;
                      transactionOK = false;
                      std::cout<<"WRONG month TRANSACTION FOUND"<<'\n';
                  }
                  if (!dayOK) {
                      day = previousDay;
                      transactionOK = false;
                      std::cout<<"WRONG day TRANSACTION FOUND"<<'\n';
                  }
                  if (!incomeGroupOK) {
                      categ = 0;
                      transactionOK = false;
                      std::cout<<"WRONG incomeGroup TRANSACTION FOUND"<<'\n';
                  }
                  if (!expenseGroupOK) {
                      categ = 0;
                      transactionOK = false;
                      std::cout<<"WRONG expensesGroup TRANSACTION FOUND"<<'\n';
                  }
                  if (!repeatOK) {
                      repeat = 0;
                      transactionOK = false;
                      std::cout<<"WRONG repeatOption TRANSACTION FOUND"<<'\n';
                  }


                  if (transactionOK)
                  {
                    previousDay = day;
                    previousMonth = month;
                  }

              //Add new transaction, if not all values could be gathered set these as default (or in case of month, the same as previous element)
              if (income){
                 RepetitionOption repOption = static_cast<RepetitionOption>(repeat);
                 Transaction tArticle(name, price, month, day, categ, repOption, income);
                 this->addTransaction(tArticle);
                 if (!transactionOK){
                                     sFaultyTransactionInfo faultyTransaction; faultyTransaction.month = month; faultyTransaction.id=Yearly_Articles[month].size()-1;
                                     listOfFaultyTransactionsInfo.push_back(faultyTransaction);
                                     allTransactionsOk = false;
                                     std::cout<<"FAULTY INCOME FOUND: "<<name <<" ID: "<<faultyTransaction.id<<'\n';
                                    }
              } else {
                 RepetitionOption repOption = static_cast<RepetitionOption>(repeat);
                 Transaction tArticle(name, price, month, day, categ, repOption);
                 this->addTransaction(tArticle);
                 if (!transactionOK){
                                     sFaultyTransactionInfo faultyTransaction; faultyTransaction.month = month; faultyTransaction.id=Yearly_Articles[month].size()-1;
                                     listOfFaultyTransactionsInfo.push_back(faultyTransaction);
                                     allTransactionsOk = false;
                                     std::cout<<"FAULTY EXPENSE FOUND: "<<name <<" ID: "<<faultyTransaction.id<<'\n';
                                    }
                }

            }
     }
     loaddata_File.close();
     return true;
}

bool Account::save_Data()
{
   this->sortTransactionsByDate();
   std::ofstream savedata_File;
   savedata_File.open(ACCOUNT_FOLDER_PATH+"/data_"+std::to_string(this->Year)+".txt");
   for (size_t i= 0; i!= 12; ++i)  //Iterate through all months and articles in each month
   {
       for (std::vector<Transaction>::iterator it = Yearly_Articles[i].begin(); it != Yearly_Articles[i].end(); ++it)
       {
           savedata_File<<it->Amount
                       <<'\t'<<it->Month
                      <<'\t'<<it->Day
                     <<'\t'<<it->IsIncome
                    <<'\t'<<it->Group
                   <<'\t'<<it->Repetition_Option
                  <<'\t'<<it->Name
                 <<'\n';
       }
   }
   savedata_File.close();
   return true;
}

void Account::loadExpensesGroups()
{
    ExpensesGroupsNames.clear();
    ExpensesGroupsAmounts.clear();
    std::ifstream loadGroupsFile;
    loadGroupsFile.open(ACCOUNT_FOLDER_PATH+"/ExpensesGroups.txt");

    //"Not classified" group won't be stored on file.
    if (ACCOUNT_LANGUAGE == ENGLISH)
    {
        this->ExpensesGroupsNames.push_back("Not classified");
        this->ExpensesGroupsAmounts.push_back(0);
    }
    else if (ACCOUNT_LANGUAGE == GERMAN)
    {
        this->ExpensesGroupsNames.push_back("Nicht klassifiziert");
        this->ExpensesGroupsAmounts.push_back(0);
    }
    else if (ACCOUNT_LANGUAGE == SPANISH)
    {
        this->ExpensesGroupsNames.push_back("Sin clasificar");
        this->ExpensesGroupsAmounts.push_back(0);
    }

    std::string line;
    if (loadGroupsFile){                        //If groups file exists, load groups.
        while (std::getline(loadGroupsFile, line))
        {
            if (!line.empty())
            {
                this->ExpensesGroupsNames.push_back(line);
                this->ExpensesGroupsAmounts.push_back(0);
            }
        }
    } else   {                                  //Else if no file exist, create a file with default groups.
        std::ofstream saveGroupsFile;
        saveGroupsFile.open(ACCOUNT_FOLDER_PATH+"/ExpensesGroups.txt");

        if (ACCOUNT_LANGUAGE == ENGLISH)
        {
            saveGroupsFile<<"Food"<<'\n'
                        <<"House"<<'\n'
                       <<"Transportation"<<'\n'
                      <<"Gifts"<<'\n'
                     <<"Miscellaneous";
            saveGroupsFile.close();
            this->ExpensesGroupsNames.push_back("Food");
            this->ExpensesGroupsNames.push_back("House");
            this->ExpensesGroupsNames.push_back("Transportation");
            this->ExpensesGroupsNames.push_back("Gifts");
            this->ExpensesGroupsNames.push_back("Miscellaneous");
        }
        else if (ACCOUNT_LANGUAGE == GERMAN)
        {
            saveGroupsFile<<"Essen"<<'\n'
                        <<"Haus"<<'\n'
                       <<"Verkehr"<<'\n'
                      <<"Geschenke"<<'\n'
                     <<"Sonstiges";
            saveGroupsFile.close();
            this->ExpensesGroupsNames.push_back("Essen");
            this->ExpensesGroupsNames.push_back("Haus");
            this->ExpensesGroupsNames.push_back("Verkehr");
            this->ExpensesGroupsNames.push_back("Geschenke");
            this->ExpensesGroupsNames.push_back("Sonstiges");
        }
        else if (ACCOUNT_LANGUAGE == SPANISH)
        {
            saveGroupsFile<<"Comida"<<'\n'
                        <<"Casa"<<'\n'
                       <<"Transporte"<<'\n'
                      <<"Regalos"<<'\n'
                     <<"Misceláneo";
            saveGroupsFile.close();
            this->ExpensesGroupsNames.push_back("Comida");
            this->ExpensesGroupsNames.push_back("Casa");
            this->ExpensesGroupsNames.push_back("Transporte");
            this->ExpensesGroupsNames.push_back("Regalos");
            this->ExpensesGroupsNames.push_back("Misceláneo");
        }

        this->ExpensesGroupsAmounts.push_back(0);
        this->ExpensesGroupsAmounts.push_back(0);
        this->ExpensesGroupsAmounts.push_back(0);
        this->ExpensesGroupsAmounts.push_back(0);
        this->ExpensesGroupsAmounts.push_back(0);
    }
}

void Account::saveExpensesGroups()
{
    std::ofstream saveGroupsFile;
    saveGroupsFile.open(ACCOUNT_FOLDER_PATH+"/ExpensesGroups.txt");

        if (ExpensesGroupsNames.size() > 0)
        {
            for (std::vector<std::string>::iterator it = ExpensesGroupsNames.begin()+1; it != ExpensesGroupsNames.end(); ++it) { //Don't save "Not classified" to file. +1
                saveGroupsFile<<*it<<'\n';
            }
        }

    saveGroupsFile.close();
}

void Account::loadIncomeGroups()
{
    IncomeGroupsNames .clear();
    IncomeGroupsAmounts.clear();
    std::ifstream loadIncomeGroupsFile;
    loadIncomeGroupsFile.open(ACCOUNT_FOLDER_PATH+"/IncomeGroups.txt");

    //"Not classified" group won't be stored on file.
    if (ACCOUNT_LANGUAGE == ENGLISH)
    {
        this->IncomeGroupsNames.push_back("Not classified");
        this->IncomeGroupsAmounts.push_back(0);
    }
    else if (ACCOUNT_LANGUAGE == GERMAN)
    {
        this->IncomeGroupsNames.push_back("Nicht klassifiziert");
        this->IncomeGroupsAmounts.push_back(0);
    }
    else if (ACCOUNT_LANGUAGE == SPANISH)
    {
        this->IncomeGroupsNames.push_back("Sin clasificar");
        this->IncomeGroupsAmounts.push_back(0);
    }

    if (loadIncomeGroupsFile){                           //If groups file exists, load groups.
        std::string line;
        while (std::getline(loadIncomeGroupsFile, line))
        {
            if (!line.empty())
            {
                this->IncomeGroupsNames.push_back(line);
                this->IncomeGroupsAmounts.push_back(0);
            }
        }
    } else  {                                           //Else if no file exist, create a file with default groups.
        std::ofstream saveIncomeGroupsFile;
        saveIncomeGroupsFile.open(ACCOUNT_FOLDER_PATH+"/IncomeGroups.txt");

        if (ACCOUNT_LANGUAGE == ENGLISH)
        {
            saveIncomeGroupsFile<<"Salary"<<'\n'
                        <<"Sales"<<'\n'
                      <<"Interests"<<'\n'
                     <<"Gifts";
            saveIncomeGroupsFile.close();
            this->IncomeGroupsNames.push_back("Salary");
            this->IncomeGroupsNames.push_back("Sales");
            this->IncomeGroupsNames.push_back("Interests");
            this->IncomeGroupsNames.push_back("Gifts");
        }
        else if (ACCOUNT_LANGUAGE == GERMAN)
        {
            saveIncomeGroupsFile<<"Gehalt"<<'\n'
                        <<"Verkaufen"<<'\n'
                      <<"Zinsen"<<'\n'
                     <<"Geschenke";
            saveIncomeGroupsFile.close();
            this->IncomeGroupsNames.push_back("Gehalt");
            this->IncomeGroupsNames.push_back("Verkaufen");
            this->IncomeGroupsNames.push_back("Zinsen");
            this->IncomeGroupsNames.push_back("Geschenkt");
        }
        else if (ACCOUNT_LANGUAGE == SPANISH)
        {
            saveIncomeGroupsFile<<"Salario"<<'\n'
                        <<"Ventas"<<'\n'
                      <<"Intereses"<<'\n'
                     <<"Regalos";
            saveIncomeGroupsFile.close();
            this->IncomeGroupsNames.push_back("Salario");
            this->IncomeGroupsNames.push_back("Ventas");
            this->IncomeGroupsNames.push_back("Intereses");
            this->IncomeGroupsNames.push_back("Regalos");
        }

        this->IncomeGroupsAmounts.push_back(0);
        this->IncomeGroupsAmounts.push_back(0);
        this->IncomeGroupsAmounts.push_back(0);
        this->IncomeGroupsAmounts.push_back(0);
    }
}

void Account::saveIncomeGroups()
{    
    std::ofstream saveIncomeGroupsFile;
    saveIncomeGroupsFile.open(ACCOUNT_FOLDER_PATH+"/IncomeGroups.txt");

        int GroupCounter = 0;
        if (IncomeGroupsNames.size() > 0)
        {
            for (std::vector<std::string>::iterator it = IncomeGroupsNames.begin()+1; it != IncomeGroupsNames.end(); ++it) { //+1 don't save "Not classified" to file.
                saveIncomeGroupsFile<<*it<<'\n';
                std::cout<<"Saving current group: "<<GroupCounter<<" "<<*it<<'\n';
                ++GroupCounter;
            }
        }

    saveIncomeGroupsFile.close();
}

void Account::clear_Year()  ///Clear all Articles
{
    for (int month=0; month!=12; ++month)
    {
        Yearly_Articles[month].clear();
    }
    NumberOfTransactions = 0;
    Total_Expenses = 0.0;
    Total_Income  = 0.0;
    totalNumberOfIncomeElements = 0;
    totalNumberOfExpensesElements = 0;

    //Groups expenses and incomes just need to be set to zero again
    for (std::vector<double>::iterator it = ExpensesGroupsAmounts.begin(); it != ExpensesGroupsAmounts.end(); ++it){
        *it = 0.0;
    }

    for (std::vector<double>::iterator it2 = IncomeGroupsAmounts.begin(); it2 != IncomeGroupsAmounts.end(); ++it2){
        *it2 = 0.0;
    }
}

void Account::clearAccountProperties(bool resetCustomColors)
{
    ACCOUNT_NAME                     = "";
    ACCOUNT_FOLDER_PATH              = "";
    ACCOUNT_ICON_PATH_NAME           = "";
    ACCOUNT_LANGUAGE                 = ENGLISH;
    ACCOUNT_CURRENCY                 = EURO;
    ACCOUNT_CURRENT_COLOR_THEME      = 0;

    if (resetCustomColors || (!PropertyFileExists))
    {
        setCustomColorElements(13, 4, 9, 7, 36, 13, 4, 9, 16, 8, 8 , 13, true, false);
        std::cout<<"Custom Colors Set To Default"<<'\n';
    }
}

double Account::getHighestMonthlyExpenses()   ///Can probably be optimized
{
    double highestExp = 0;
    highestExp =  this->getExpensesInMonth(0);
    for (int i = 1; i!=12; ++i)
    {
        double tempExp = this->getExpensesInMonth(i);
        if (tempExp > highestExp)
        {
            highestExp = tempExp;
        }
    }
    return highestExp;
}

double Account::getHighestMonthlyIncome()
{
    double highestIncomeInAMonth = 0;
    highestIncomeInAMonth = this->getIncomeInMonth(0);
    for (int i = 1; i != 12; ++i)
    {
        double tempIncome = this->getIncomeInMonth(i);
        if (tempIncome > highestIncomeInAMonth)
        {
            highestIncomeInAMonth = tempIncome;
        }
    }
    return highestIncomeInAMonth;
}

int Account::getTotalNumberOfExpensesTransactionsInGroup(const int &group)
{
    int numberOfArticlesOfGroup = 0;
    for (std::vector<std::vector<Transaction>>::iterator it1 = Yearly_Articles.begin(); it1 != Yearly_Articles.end(); ++it1)
    {
        for (std::vector<Transaction>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
        {
            if ((*it2).Group == group && !(it2->IsIncome))
            {
                ++numberOfArticlesOfGroup;
            }
        }
    }
    return numberOfArticlesOfGroup;
}

int Account::getTotalNumberOfIncomeTransactionsInGroup(const int &group)
{
    int numberOfItemsInGroup = 0;
    for (std::vector<std::vector<Transaction>>::iterator it1 = Yearly_Articles.begin(); it1 != Yearly_Articles.end(); ++it1)
    {
        for (std::vector<Transaction>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
        {
            if ((it2->Group) == group && (it2->IsIncome))
            {
                ++numberOfItemsInGroup;
            }
        }
    }

    return numberOfItemsInGroup;
}

void Account::swapGroupsForExpensesTransactions(const int &oldGroup, const int &newGroup) //SWAP GROUPS ONLY FOR EXPENSES!!!!!!!
{
    for (std::vector<std::vector<Transaction>>::iterator it1 = Yearly_Articles.begin(); it1!= Yearly_Articles.end(); ++it1)
    {
        for (std::vector<Transaction>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
        {
            if ((*it2).Group == oldGroup && ((*it2).IsIncome == false))
            {
                (*it2).Group = newGroup;                 ///Set as Not Classified
            }

            else if ((*it2).Group > oldGroup && ((*it2).IsIncome == false))
            {
                (*it2).Group = ((*it2).Group-1); ///Shift transactions with groups above the one deleted to one position below
            }
        }
    }
}

void Account::swapGroupForIncomeTransactions(const int &oldGroup, const int &newGroup) //SWAP GROUPS ONLY FOR INCOME!!!!!!!
{
    for (std::vector<std::vector<Transaction>>::iterator it1 = Yearly_Articles.begin(); it1!= Yearly_Articles.end(); ++it1)
    {
        for (std::vector<Transaction>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
        {
            if (((*it2).Group == oldGroup) && ((*it2).IsIncome))
            {
                (*it2).Group = newGroup;                 ///Set as Not Classified
            }

            else if (((*it2).Group > oldGroup) && ((*it2).IsIncome))
            {
                (*it2).Group = ((*it2).Group-1); ///Shift transactions with groups above to one position below
            }
        }
    }
}

void Account::addIncomeGroup(const std::string &groupName)
{
    IncomeGroupsNames.push_back(groupName);
    IncomeGroupsAmounts.push_back(0.0);
}

void Account::addExpensesGroup(const std::string &groupName)
{
    ExpensesGroupsNames.push_back(groupName);
    ExpensesGroupsAmounts.push_back(0.0);
}

void Account::deleteExpensesGroup(const int &group)
{
    std::vector<std::string>::iterator groupNameIterator        = ExpensesGroupsNames.begin();
    std::vector<double>::iterator      groupExpensesIterator    = ExpensesGroupsAmounts.begin();

    ExpensesGroupsNames.erase(groupNameIterator+group);
    ExpensesGroupsAmounts.erase(groupExpensesIterator+group);
}

void Account::deleteIncomeGroup(const int &group)
{
    std::vector<std::string>::iterator groupNameIterator        = IncomeGroupsNames.begin();
    std::vector<double>::iterator      groupAmountIterator      = IncomeGroupsAmounts.begin();

    IncomeGroupsNames.erase(groupNameIterator+group);
    IncomeGroupsAmounts.erase(groupAmountIterator+group);
}

std::vector<Transaction> Account::getListOfExpensesItemsOfGroup(const int &group)
{
    std::vector<Transaction> listOfArticles;
    listOfArticles.clear();

    for (std::vector<std::vector<Transaction>>::iterator yearIterator = Yearly_Articles.begin();
         yearIterator != Yearly_Articles.end(); ++yearIterator)
    {
        for (std::vector<Transaction>::iterator monthIterator =(*yearIterator).begin();
             monthIterator != (*yearIterator).end(); ++monthIterator)
        {
            if (((*monthIterator).Group == group) && (!(*monthIterator).IsIncome))
            {
                listOfArticles.push_back(*monthIterator);
            }
        }
    }
    return listOfArticles;
}

std::vector<Transaction> Account::getListOfIncomeItemsOfGroup(const int &group)
{
    std::vector<Transaction> listOfArticles;
    listOfArticles.clear();

    for (std::vector<std::vector<Transaction>>::iterator yearIterator = Yearly_Articles.begin();
         yearIterator != Yearly_Articles.end(); ++yearIterator)
    {
        for (std::vector<Transaction>::iterator monthIterator =(*yearIterator).begin();
             monthIterator != (*yearIterator).end(); ++monthIterator)
        {
            if (((*monthIterator).Group == group) && ((*monthIterator).IsIncome))
            {
                listOfArticles.push_back(*monthIterator);
            }
        }
    }
    return listOfArticles;
}


void Account::setElementsToRepeat(std::vector<Transaction> &newElementsAdded)
{
    time_t Time = time(nullptr);
    struct tm * current_Time = localtime(&Time);

    int current_Year  = current_Time->tm_year+1900;
    int current_Month = current_Time->tm_mon;
    int current_Day   = current_Time->tm_mday;    
    int current_DayId = current_Time->tm_yday+1;

    if (Year < current_Year){
        current_Month = 11;
        current_Day   = 31;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////THE FOLLOWING WORKS ONLY FOR WEEKLY REPETITIONS//////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for (int monthAnalized = 0; monthAnalized <= current_Month; ++monthAnalized)
        {
            std::vector<std::vector<Transaction>>::iterator MonthsIterator = Yearly_Articles.begin()+monthAnalized;
            bool newElementAdded = false;

            for (std::vector<Transaction>::iterator Articleit1 = (*MonthsIterator).begin(); Articleit1 != (*MonthsIterator).end(); ++Articleit1) {

                if (newElementAdded)
                {
                    ///Reset Articleit1. When a new element is added elements are reallocated and invalidates all iterators.
                    Articleit1 = (*MonthsIterator).begin();
                    newElementAdded = false;
                }

                    if ( ((*Articleit1).Repetition_Option) == REPEAT_EVERY_WEEK || ((*Articleit1).Repetition_Option) == REPEAT_EVERY_TWO_WEEKS)
                    {
                        int startIdDayForGivenMonth[12];
                        if (this->isCurrentYearLeap()) {
                            if (Year < current_Year) {current_DayId = 366;}
                            startIdDayForGivenMonth[0]  = 0;
                            startIdDayForGivenMonth[1]  = 31;
                            startIdDayForGivenMonth[2]  = 60;
                            startIdDayForGivenMonth[3]  = 91;
                            startIdDayForGivenMonth[4]  = 121;
                            startIdDayForGivenMonth[5]  = 152;
                            startIdDayForGivenMonth[6]  = 182;
                            startIdDayForGivenMonth[7]  = 213;
                            startIdDayForGivenMonth[8]  = 244;
                            startIdDayForGivenMonth[9]  = 274;
                            startIdDayForGivenMonth[10] = 305;
                            startIdDayForGivenMonth[11] = 335;
                        } else if (!(this->isCurrentYearLeap())) {
                            if (Year < current_Year) {current_DayId = 365;}
                            startIdDayForGivenMonth[0]  = 0;
                            startIdDayForGivenMonth[1]  = 31;
                            startIdDayForGivenMonth[2]  = 59;
                            startIdDayForGivenMonth[3]  = 90;
                            startIdDayForGivenMonth[4]  = 120;
                            startIdDayForGivenMonth[5]  = 151;
                            startIdDayForGivenMonth[6]  = 181;
                            startIdDayForGivenMonth[7]  = 212;
                            startIdDayForGivenMonth[8]  = 243;
                            startIdDayForGivenMonth[9]  = 273;
                            startIdDayForGivenMonth[10] = 304;
                            startIdDayForGivenMonth[11] = 334;
                        }
                                ///GET DAY ID FOR CURRENT ARTICLE/TRANSACCION
                                int daysToIncrement = 7;  ///IF REPEAT_IN_1WEEK
                                if (((*Articleit1).Repetition_Option) == REPEAT_EVERY_TWO_WEEKS){
                                    daysToIncrement = 14;
                                }

                                int oldDayId = (startIdDayForGivenMonth[Articleit1->Month]) + Articleit1->Day;

                                int newDayId = oldDayId+daysToIncrement;
                                if (newDayId <= current_DayId){  //Ensures that the new date won't be later than the present (which at the same time never will be later than the 365/366 days of the year)
                                        ///COMPUTE MONTH AND DAY FOR NEW ID (dayId + daysToIncrement)
                                        int monthFromId = -1; //Because next loop will fullfill the condition at least once and it will increment monthFromId
                                        int dayFromId   = 0; //Day in month, to which the new element will be copied.
                                        for (const int *i = std::begin(startIdDayForGivenMonth); i != std::end(startIdDayForGivenMonth); ++i)
                                        {
                                            if (newDayId > *i){
                                                monthFromId++;
                                            }
                                            else {
                                                break;
                                            }
                                        }
                                        dayFromId = newDayId - startIdDayForGivenMonth[monthFromId];


                                        const double      lookingForPrice      = (*Articleit1).Amount;
                                        const int         lookingForGroup      = (*Articleit1).Group;
                                        const std::string lookingForName       = (*Articleit1).Name;
                                        const bool        lookingForIsIncome   = (*Articleit1).IsIncome;
                                        const int         preserveRepetitionOption = (*Articleit1).Repetition_Option;
                                        /// CHECK IF ELEMENT WITH THIS INFORMATION ALREADY EXISTS IN FINAL MONTH, DO NOT CHECK IF newDayId > 366 || 365 (this is alredy verified by if enclosure  if(newDayId <= current_DayId) )
                                        /// ITERATE THROUGH ALL ELEMENTS OF NEW MONTH (IT MAY BE THE SAME MONTH monthFromId)
                                        /// AND COMPARE THE ONES SEVEN DAYS AFTER OR 14 DAYS AFTER(dayFromId)
                                        /// IF NOTHING IS FOUND (NOTHING WITH SAME NAME, PRICE/AMOUNT, CATEGORY), COPY THE ELEMENT.
                                        bool itemAlreadyCopied = false;
                                           std::vector<std::vector<Transaction>>::iterator checkMonth = Yearly_Articles.begin()+monthFromId; //monthFromId is the final month to which the new copy will land.
                                            {
                                                for (std::vector<Transaction>::iterator checkElement = checkMonth->begin(); checkElement != checkMonth->end(); ++checkElement)
                                                {
                                                    if (    (lookingForName           == (*checkElement).Name)
                                                         && (lookingForPrice          == (*checkElement).Amount)
                                                         && (lookingForGroup          == (*checkElement).Group)
                                                         && (  dayFromId              == (*checkElement).Day)
                                                         && (lookingForIsIncome       == (*checkElement).IsIncome)   ) //Don't Check Repeat. Otherwise element will be repeated after deleting previous to repeat
                                                    {
                                                        itemAlreadyCopied = true;
                                                        break;
                                                    }
                                                }

                                                if (itemAlreadyCopied == false)
                                                {
                                                    (*Articleit1).Repetition_Option = DO_NOT_REPEAT; //Set original transaction as DO_NOT_REPEAT
                                                    ///ADD NEW COPY TO CURRENT YEAR
                                                    if ((*Articleit1).IsIncome)
                                                    {
                                                        Transaction copyArticle(lookingForName,
                                                                            lookingForPrice,
                                                                            monthFromId,
                                                                            dayFromId,
                                                                            lookingForGroup,
                                                                            static_cast<RepetitionOption>(preserveRepetitionOption),
                                                                            true);
                                                        this->addTransaction(copyArticle);
                                                        newElementAdded = true;
                                                        newElementsAdded.push_back(copyArticle);

                                                    }
                                                    else if (!(*Articleit1).IsIncome)
                                                    {
                                                        Transaction copyArticle(lookingForName,
                                                                            lookingForPrice,
                                                                            monthFromId,
                                                                            dayFromId,
                                                                            lookingForGroup,
                                                                            static_cast<RepetitionOption>(preserveRepetitionOption));
                                                        this->addTransaction(copyArticle);
                                                        newElementAdded = true;
                                                        newElementsAdded.push_back(copyArticle);
                                                    }
                                                }
                                            }
                                }
                    }
            }
        }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////THE FOLLOWING WORKS ONLY FOR MONTHLY REPETITIONS/////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (current_Month > 0 )  ///If current month is february or after, and year to preocess is current or before
    {
        for (int i = 0; i != current_Month; ++i)
        {
           std::vector<std::vector<Transaction>>::iterator MonthsIterator = Yearly_Articles.begin()+i;
           for (std::vector<Transaction>::iterator it1 = (*MonthsIterator).begin(); it1 != (*MonthsIterator).end(); ++it1)
               {
                  bool itemAlreadyExists = false;
                  if ( ((*it1).Repetition_Option) == REPEAT_EVERY_MONTH)
                  {
                    ////Point to next month
                    std::vector<std::vector<Transaction>>::iterator NextMonthIterator = Yearly_Articles.begin()+i+1;

                      ////If next month is empty (and the date has been reached) just add the element to repeat
                      if ((*NextMonthIterator).empty() && (it1->Day <= current_Day))
                      {
                          if ((*it1).IsIncome)
                          {
                              double      price  = (*it1).Amount;
                              int         month  = (*it1).Month+1;
                              int         day    = (*it1).Day;
                              int         categ  = (*it1).Group;
                              std::string name   = (*it1).Name;
                              //Check if new month can have the new day assigned
                              if (day > getNumberOfDaysInMonth(this->Year,month)){
                                  day = getNumberOfDaysInMonth(this->Year, month);
                              }

                              Transaction copyArticle(name, price, month, day, categ, REPEAT_EVERY_MONTH, true);
                              this->addTransaction(copyArticle);
                              newElementsAdded.push_back(copyArticle);
                              it1->Repetition_Option = DO_NOT_REPEAT;
                          }
                          else if (!(*it1).IsIncome)
                          {
                              double      price  = (*it1).Amount;
                              int         month  = (*it1).Month+1;
                              int         day    = (*it1).Day;
                              int         categ  = (*it1).Group;
                              std::string name   = (*it1).Name;
                              //Check if new month can have the new day assigned
                              if (day > getNumberOfDaysInMonth(this->Year,month)){
                                  day = getNumberOfDaysInMonth(this->Year, month);
                              }

                              Transaction copyArticle(name, price, month, day, categ, REPEAT_EVERY_MONTH);
                              this->addTransaction(copyArticle);
                              newElementsAdded.push_back(copyArticle);
                              it1->Repetition_Option  = DO_NOT_REPEAT;
                          }
                      }
                      else
                      {
                          ////If next month is not empty Verify if articles/transactions were already copied
                          for (std::vector<Transaction>::iterator it2 = (*NextMonthIterator).begin(); it2 != (*NextMonthIterator).end(); ++it2)
                          {
                              if (    ((*it1).Name      == (*it2).Name)
                                   && ((*it1).Amount     == (*it2).Amount)
                                   && ((*it1).Group  == (*it2).Group)
                                   && ((*it1).Day       == (*it2).Day)
                                   && ((*it1).IsIncome       == (*it2).IsIncome))
                              {
                                  //std::cout<<"Item already exists, original set as DO_NOT_REPEAT"<<'\n';
                                  (*it1).Repetition_Option = DO_NOT_REPEAT;
                                  itemAlreadyExists = true;
                                  break;
                              }
                          }

                              ///If item doesn't exist copy it to next month
                              if (itemAlreadyExists == false)
                              {
                                  if ( (((*it1).Month+1) == current_Month) && ((*it1).Day > current_Day) ){
                                      continue; ///If current date is reached don't add element.
                                  }

                                  if ((*it1).IsIncome)
                                  {
                                      double      price  = (*it1).Amount;
                                      int         month  = (*it1).Month+1;
                                      int         day    = (*it1).Day;
                                      int         categ  = (*it1).Group;
                                      std::string name   = (*it1).Name;
                                      //Check if new month can have the new day assigned
                                      if (day > getNumberOfDaysInMonth(this->Year,month)){
                                          day = getNumberOfDaysInMonth(this->Year, month);
                                      }

                                      Transaction copyArticle(name, price, month, day, categ, REPEAT_EVERY_MONTH, true);
                                      this->addTransaction(copyArticle);
                                      newElementsAdded.push_back(copyArticle);
                                      it1->Repetition_Option = DO_NOT_REPEAT;
                                      continue;
                                  }
                                  else if (!(*it1).IsIncome)
                                  {
                                      double      price  = (*it1).Amount;
                                      int         month  = (*it1).Month+1;
                                      int         day    = (*it1).Day;
                                      int         categ  = (*it1).Group;
                                      std::string name   = (*it1).Name;
                                      //Check if new month can have the new day assigned
                                      if (day > getNumberOfDaysInMonth(this->Year,month)){
                                          day = getNumberOfDaysInMonth(this->Year, month);
                                      }

                                      Transaction copyArticle(name, price, month, day, categ, REPEAT_EVERY_MONTH);
                                      this->addTransaction(copyArticle);
                                      newElementsAdded.push_back(copyArticle);
                                      it1->Repetition_Option = DO_NOT_REPEAT;
                                      continue;
                                  }
                              }
                      }

                  }
               }
        }
    }
}

void Account::editTransaction(Transaction &oldArtInfo, Transaction &newArtInfo)
{
    ///IF NO CHANGES WERE MADE, DON'T CHANGE REPEATED ELEMENTS
    if (    (newArtInfo.Name      == oldArtInfo.Name)
         && (newArtInfo.Amount     == oldArtInfo.Amount)
         && (newArtInfo.Group  == oldArtInfo.Group)
         && (newArtInfo.Day       == oldArtInfo.Day)
         && (newArtInfo.IsIncome       == oldArtInfo.IsIncome)
         && (newArtInfo.Repetition_Option== oldArtInfo.Repetition_Option)
         && (newArtInfo.Month     == oldArtInfo.Month)
            ) {
        return;
    }

    ///JUST REPLACE OLD TRANSACTION WITH NEW ONE.

        if ((oldArtInfo.Month <= newArtInfo.Month))
        {
            std::vector<std::vector<Transaction>>::iterator deleteIterator = Yearly_Articles.begin()+oldArtInfo.Month;
            for (std::vector<Transaction>::iterator itemToDelete = (*deleteIterator).begin();
                 itemToDelete != (*deleteIterator).end(); ++itemToDelete)
                {
                if (    ((*itemToDelete).Name      == oldArtInfo.Name)
                     && ((*itemToDelete).Amount     == oldArtInfo.Amount)
                     && ((*itemToDelete).Group  == oldArtInfo.Group)
                     && ((*itemToDelete).Day       == oldArtInfo.Day)
                     && ((*itemToDelete).IsIncome       == oldArtInfo.IsIncome)
                     && ((*itemToDelete).Repetition_Option== oldArtInfo.Repetition_Option)
                   ) {
                    --NumberOfTransactions;
                    if (!(*itemToDelete).IsIncome){
                        ///Decrease total expenditures
                        Total_Expenses-=(itemToDelete->Amount);
                        ///Decrease total expenses for the specific group
                        std::vector<double>::iterator itExpenses = ExpensesGroupsAmounts.begin();
                        *(itExpenses+(itemToDelete->Group)) -= itemToDelete->Amount;
                        ///Substract 1 to the expenses of income elements
                        --totalNumberOfExpensesElements;
                    }

                    else if ((*itemToDelete).IsIncome) {
                        ///Decrease total income
                        Total_Income -= (itemToDelete->Amount);
                        ///Decrease total income for specific group
                        std::vector<double>::iterator itIncome = IncomeGroupsAmounts.begin();
                        *(itIncome+(itemToDelete->Group)) -= itemToDelete->Amount;
                        ///Substract 1 to the number of income elements
                        --totalNumberOfIncomeElements;
                    }

                    (*deleteIterator).erase(itemToDelete);
                    break;
                }
            }
        }

        else if (oldArtInfo.Month > newArtInfo.Month)
        {
            for (std::vector<std::vector<Transaction>>::iterator deleteIterator = Yearly_Articles.begin()+newArtInfo.Month;
                 deleteIterator != Yearly_Articles.end(); ++deleteIterator){

                for (std::vector<Transaction>::iterator itemToDelete = (*deleteIterator).begin();
                     itemToDelete != (*deleteIterator).end(); ++itemToDelete)
                    {
                    if (    ((*itemToDelete).Name      == oldArtInfo.Name)
                         && ((*itemToDelete).Amount     == oldArtInfo.Amount)
                         && ((*itemToDelete).Group  == oldArtInfo.Group)
                         && ((*itemToDelete).Day       == oldArtInfo.Day)
                         && ((*itemToDelete).IsIncome       == oldArtInfo.IsIncome)
                         && ((*itemToDelete).Repetition_Option== oldArtInfo.Repetition_Option)
                       ) {
                        --NumberOfTransactions;
                        if (!(*itemToDelete).IsIncome){
                            ///Decrease total expenditures
                            Total_Expenses-=(itemToDelete->Amount);
                            ///Decrease total expenses for the specific group
                            std::vector<double>::iterator itExpenses = ExpensesGroupsAmounts.begin();
                            *(itExpenses+(itemToDelete->Group)) -= itemToDelete->Amount;
                            ///Substract 1 to the number of expenses elements
                            --totalNumberOfExpensesElements;
                        }

                        else if ((*itemToDelete).IsIncome) {
                            ///Decrease total income
                            Total_Income -= (itemToDelete->Amount);
                            ///Decrease total income for specific group
                            std::vector<double>::iterator itIncome = IncomeGroupsAmounts.begin();
                            *(itIncome+(itemToDelete->Group)) -= itemToDelete->Amount;
                            ///Substract 1 to the number of income elements
                            --totalNumberOfIncomeElements;
                        }

                        (*deleteIterator).erase(itemToDelete);
                        break;
                    }
                }
            }
        }
        this->addTransaction(newArtInfo);
}

double Account::getPercentageOfIncomeGroup(const int &groupId)
{
    //Rename getAmountOfIncomeGroup)
    std::vector<double>::iterator groupIncomeIterator = IncomeGroupsAmounts.begin()+groupId;

    if (*groupIncomeIterator != 0.0){
        return (*groupIncomeIterator/getTotalIncomeInYear());
    }
    else {
        return 0.0;
    }
}

double Account::getPercentageOfExpensesGroup(const int &groupId)
{
    std::vector<double>::iterator groupExpenseIterator = ExpensesGroupsAmounts.begin()+groupId;

    if (*groupExpenseIterator != 0.0){
        return (*groupExpenseIterator/getTotalExpensesInYear());
    }
    else {
        return 0.0;
    }
}
