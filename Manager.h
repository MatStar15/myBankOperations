//
// Created by Mat on 05/09/2024.
//



#ifndef MYBANKOPERATIONS_MANAGER_H
#define MYBANKOPERATIONS_MANAGER_H

#include <fstream>
#include <vector>
#include <stdexcept>
#include "Account.h"
#include "MoneyTransfer.h"




class Manager {
private:

    static Manager* instance;

    Manager(){
        loadAccounts();
        loadTransfers();
    }

    static std::vector<std::shared_ptr<Account>> accounts;
    static std::vector<std::shared_ptr<MoneyTransfer>> transfers;

    static int transferCount;
    static int accountCount;

    static void saveAllAccounts();
    static void saveAllTransfers();

public:
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    static Manager* getInstance(){
        if(instance == nullptr){
            instance = new Manager();
        }
        return instance;
    }

    static void saveAccount(const Account &account);
    static void saveTransfer(const MoneyTransfer &moneyTransfer);

    static void addAccount(const std::shared_ptr<Account>& account);
    static void addTransfer(const std::shared_ptr<MoneyTransfer>& moneyTransfer);

    static void wipe();
    static void save();


    static void loadAccounts();
    static void loadTransfers();

    static std::shared_ptr<Account> getAccount(int accountNumber);
    static std::shared_ptr<MoneyTransfer> getTransfer(int transferNumber);

    static std::vector<std::shared_ptr<Account>> getHolderAccounts(const std::string &holderName);
    static std::vector<std::shared_ptr<MoneyTransfer>> getHolderSenderTransfers(const int senderAccountNumber);
    static std::vector<std::shared_ptr<MoneyTransfer>> getHolderReceiverTransfers(const int receiverAccountNumber);

    static int getTransferCount(){
        return transferCount;
    }

    static int getAccountCount(){
        return accountCount;
    }

    static void displayAllAccounts(){
        for(const auto &account : accounts){
            account->displayAccount();
        }
    }

    static void displayAllTransfers(){
        for(const auto &transfer : transfers){
            transfer->displayTransfer();
        }
    }

    ~Manager();


};



#endif //MYBANKOPERATIONS_MANAGER_H
