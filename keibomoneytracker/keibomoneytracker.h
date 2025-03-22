/*
* Copyright © 2020-2025 Carlos Constancio Dominguez Martinez
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

#ifndef BUY_DATA_H
#define BUY_DATA_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include <fstream>
#include <iterator>
#include <keibomoneytrackerinclude.h>

struct sFaultyTransactionInfo{
    int month = 0;
    int id = 0;
};

//---------------------------------------------------------------------------------------////-------------------------------------------------------------------------------------------//

class Transaction
{
public:

    /////////////////////////////////////////////////////////////////////////////////////////
    ///--------------------------         CONSTRUCTORS       -----------------------------///
    Transaction() = default;
    Transaction(const std::string &nam, const double &pri, const int &mon, const int &day, const int &cat, const RepetitionOption &repeat) :
        Name(nam), Amount(pri), Group(cat), Month(mon), Day(day), Repetition_Option(repeat) {}

    Transaction(const std::string &nam, const double &pri, const int &mon, const int &day, const int &cat, const RepetitionOption &repeat, const bool &income) :
        Name(nam), Amount(pri), Group(cat), Month(mon), Day(day), Repetition_Option(repeat), IsIncome(income) {}


    /////////////////////////////////////////////////////////////////////////////////////////
    ///--------------------------        PUBLIC MEMBERS      -----------------------------///
    std::string     Name       ="";
    double          Amount     = 0.0;
    int             Group      = 0;

    int             Month      = 0;
    int             Day        = 0;

    RepetitionOption            Repetition_Option     = DO_NOT_REPEAT;
    bool                        IsIncome              = false;
};


//-----------------------------------------------------------------------------------------////-----------------------------------------------------------------------------------------//

class Account
{
public:
    /////////////////////////////////////////////////////////////////////////////////////////
    ///--------------------------         CONSTRUCTORS       -----------------------------///
    Account() = default;
    Account(const int &year);
    //Account(int year) :    Year(year) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    ///--------------------------        PUBLIC MEMBERS      -----------------------------///
    std::vector<std::vector<Transaction> >  Yearly_Articles{12};

    std::vector<std::string> ExpensesGroupsNames;
    std::vector<double>      ExpensesGroupsAmounts;

    std::vector<std::string> IncomeGroupsNames;
    std::vector<double>      IncomeGroupsAmounts;

    ColorConfiguration       customColorConfiguration;

    bool allTransactionsOk;
    std::vector<sFaultyTransactionInfo> listOfFaultyTransactionsInfo;

    /////////////////////////////////////////////////////////////////////////////////////////
    ///--------------------------        MAIN FUNCTIONS      -----------------------------///
    int  addTransaction(Transaction &temp_Article);
    void editTransaction(Transaction &oldArtInfo, Transaction &newArtInfo);
    void deleteSingleTransaction (int month, int id);
    int  deleteMultipleTransactionsInMonth(const int &mon, std::vector<int> listOfItemsToDelete);

    void setElementsToRepeat(std::vector<Transaction> &newElementsAdded);

    void sortTransactionsByDate();

    void loadExpensesGroups();
    void saveExpensesGroups();

    void loadIncomeGroups();
    void saveIncomeGroups();    

    void addIncomeGroup(const std::string &groupName);
    void addExpensesGroup(const std::string &groupName);

    void deleteIncomeGroup    (const int &group);
    void deleteExpensesGroup  (const int &group);

    void swapGroupsForExpensesTransactions(const int & oldGroup, const int & newGroup);
    void swapGroupForIncomeTransactions(const int & oldGroup, const int & newGroup);

    bool load_Data();
    bool save_Data();

    bool loadAccountProperties(std::string accountName, std::string accountFolderPath);
    void saveAccountProperties();
    void setAccountProperties(std::string  accountName,
                              std::string  accountFolderPath,
                              std::string  accountIconFileName,
                              Language     accountLanguage,
                              Currency     accountCurrency,
                              unsigned int accountCurrentColorTheme)
         {
          ACCOUNT_NAME                   =accountName;
          ACCOUNT_FOLDER_PATH            =accountFolderPath;
          ACCOUNT_ICON_PATH_NAME         =accountIconFileName;
          ACCOUNT_LANGUAGE               =accountLanguage;
          ACCOUNT_CURRENCY               =accountCurrency;
          ACCOUNT_CURRENT_COLOR_THEME    =accountCurrentColorTheme;
         }
    void updateDefaultGroupsToCurrentLanguage();

    void setAccountCurrentColorTheme(unsigned int theme);
    void setAccountFolderPath(const std::string &tempFolderPath) {ACCOUNT_FOLDER_PATH = tempFolderPath;}

    inline void setCustomColorElements (const int &barIncomeSelected,
                                  const int &barIncomeUnselected,
                                  const int &barExpensesSelected,
                                  const int &barExpensesUnselected,
                                  const int &barBackground,
                                  const int &groupIncomeSelected,
                                  const int &groupIncomeUnselected,
                                  const int &groupExpensesSelected,
                                  const int &groupExpensesUnselected,
                                  const int &groupIncomeBackground,
                                  const int &groupExpensesBackground,
                                  const int &tableIncomeAmount,
                                  const bool &monthlyAmountInColor,
                                  const bool &useDarkOverall)
    {
        customColorConfiguration.colorBarIncomeSelected        = barIncomeSelected;
        customColorConfiguration.colorBarIncomeUnselected      = barIncomeUnselected;
        customColorConfiguration.colorBarExpensesSelected      = barExpensesSelected;
        customColorConfiguration.colorBarExpensesUnselected    = barExpensesUnselected;
        customColorConfiguration.colorBarBackground            = barBackground;

        customColorConfiguration.colorGroupIncomeSelected      = groupIncomeSelected;
        customColorConfiguration.colorGroupIncomeUnselected    = groupIncomeUnselected;
        customColorConfiguration.colorGroupExpensesSelected    = groupExpensesSelected;
        customColorConfiguration.colorGroupExpensesUnselected  = groupExpensesUnselected;
        customColorConfiguration.colorGroupIncomeBackground    = groupIncomeBackground;
        customColorConfiguration.colorGroupExpensesBackground  = groupExpensesBackground;

        customColorConfiguration.colorTableIncomeAmount        = tableIncomeAmount;
        customColorConfiguration.showMonthlyAmountsInColor     = monthlyAmountInColor;

        customColorConfiguration.useDarkOverallTheme           = useDarkOverall;
        customColorConfiguration.setOverallThemeColors();
    }


    /////////////////////////////////////////////////////////////////////////////////////////
    ///------------------------   FUNCTIONS TO GET INFORMATION   -------------------------///
    double  getTotalExpensesInYear()                       {return Total_Expenses;}
    double  getExpensesInMonth(const int &mon);
    double  getHighestMonthlyExpenses();
    double  getTotalExpensesOfGroup (const int &group)     {return ExpensesGroupsAmounts[group];}
    int     getTotalNumberOfExpensesTransactionsInGroup(const int &group);
    double  getPercentageOfExpensesGroup(const int &groupId);
    void    getHighestExpenseInYear_Transaction (Transaction &highestExpenseInYear);
    void    getHighestMonthlyExpensesInYear(double &amount, int &month);
    void    getLowestMonthlyExpensesInYear(double &amount, int &month);
    void    getGroupWithHighestExpensesInYear(std::string &groupName, double &amount);
    void    getGroupWithLowestExpensesInYear(std::string &groupName, double &amount);
    int     getNumberOfExpensesElementsInMonth (const int &month);

    double  getTotalIncomeInYear()                          {return Total_Income;}
    double  getIncomeInMonth(const int &mon);
    double  getHighestMonthlyIncome();
    double  getTotalIncomeOfGroup  (const int &group)          {return IncomeGroupsAmounts[group];}
    int     getTotalNumberOfIncomeTransactionsInGroup(const int &group);
    double  getPercentageOfIncomeGroup(const int &groupId);
    void    getHighestIncomeInYear_Transaction (Transaction &highestIncomeInYear);
    void    getHighestMonthlyIncomeInYear(double &amount, int &month);
    void    getLowestMonthlyIncomeInYear(double &amount, int &month);
    void    getGroupWithHighestIncomeInYear(std::string &groupName, double &amount);
    void    getGroupWithLowestIncomeInYear(std::string &groupName, double &amount);
    int     getNumberOfIncomeElementsInMonth (const int &month);

    double  getBalanceInYear();
    double  getBalanceInMonth(const int &mon);

    int     getNumberOfTransactionsInMonth(const int &mon)                {return (this->Yearly_Articles[mon].size());}
    std::vector<Transaction>    getListOfExpensesItemsOfGroup(const int &group);
    std::vector<Transaction>    getListOfIncomeItemsOfGroup(const int &group);

    void    set_Year(const int &year)                           {Year = year;}
    int     getYear()                                           {return Year;}
    void    clear_Year();
    void    clearAccountProperties(bool resetCustomColors);

    bool hasProfileImage();
    std::string getAccountName()                                {return ACCOUNT_NAME;}
    Language    getAccountLanguage()                            {return ACCOUNT_LANGUAGE;}
    Currency    getAccountCurrency()                            {return ACCOUNT_CURRENCY;}
    std::string getAccountCurrencyString();
    std::string getAccountLanguageString();
    std::string getAccountCurrencySymbol();
    unsigned int  getAccountCurrentColorTheme()                 {return ACCOUNT_CURRENT_COLOR_THEME;}
    std::string getAccountIconPath()                            {return ACCOUNT_ICON_PATH_NAME;}
    std::vector<std::string> getLanguageList();
    std::vector<std::string> getCurrencyList();
    ColorConfiguration getCustomColorConfiguration()            {return customColorConfiguration;}

    int getTotalNumberOfElements()                              {return NumberOfTransactions;}
    int getTotalNumberOfIncomeElements()                        {return totalNumberOfIncomeElements;}
    int getTotalNumberOfExpensesElements()                      {return totalNumberOfExpensesElements;}

    void getFirstElement(Transaction &firstElement);
    void getLastElement(Transaction &lastElement);
    std::string getAccountFolderPath()                          {return ACCOUNT_FOLDER_PATH;}

    inline bool isCurrentYearLeap();

    bool exportDataToCsvFile(std::string fileName, std::vector<int> &listOfYearsToExport);
    std::string deleteCommaFromText(std::string &text);

    /////////////////////////////////////////////////////////////////////////////////////////
    ///--------------------------       PRIVATE MEMBERS      -----------------------------///
private:
    bool    PropertyFileExists     = true;
    int     Year                   = 2020;
    int     NumberOfTransactions   = 0;
    double  Total_Expenses         = 0.0;
    int     totalNumberOfExpensesElements = 0;
    double  Total_Income           = 0.0;
    int     totalNumberOfIncomeElements   = 0;

    ///--------------------------     ACCOUNT PROPERTIES     -----------------------------///
    std::string  ACCOUNT_NAME                     = "";
    std::string  ACCOUNT_FOLDER_PATH              = "";
    std::string  ACCOUNT_ICON_PATH_NAME           = "";
    Language     ACCOUNT_LANGUAGE                 = ENGLISH;
    Currency     ACCOUNT_CURRENCY                 = EURO;
    unsigned int ACCOUNT_CURRENT_COLOR_THEME      = 0;
};

#endif // BUY_DATA_H
