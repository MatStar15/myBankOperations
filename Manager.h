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

    //Need to be static to be accessed by Transfer and Account constructors without getting instance of Manager every time
    static std::vector<std::shared_ptr<Account>> accounts;
    static std::vector<std::shared_ptr<MoneyTransfer>> transfers;

    void saveAllAccounts();
    void saveAllTransfers();

public:
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    static Manager* getInstance(){
        if(instance == nullptr){
            instance = new Manager();
        }
        return instance;
    }

    void saveAccount(const Account &account);
    void saveTransfer(const MoneyTransfer &moneyTransfer);

    static void addAccount(const std::shared_ptr<Account>& account);
    static void addTransfer(const std::shared_ptr<MoneyTransfer>& moneyTransfer);

    void removeTransfer(const std::shared_ptr<MoneyTransfer>& moneyTransfer);

    void wipe();
    void save();

    void loadAccounts();
    void loadTransfers();

    static std::shared_ptr<Account> getAccount(int accountNumber);
    static std::shared_ptr<MoneyTransfer> getTransfer(int transferNumber);

    std::vector<std::shared_ptr<Account>> getHolderAccounts(const std::string &holderName);
    std::vector<std::shared_ptr<MoneyTransfer>> getHolderSenderTransfers(int senderAccountNumber);
    std::vector<std::shared_ptr<MoneyTransfer>> getHolderReceiverTransfers(int receiverAccountNumber);


    static int getTransferCount(){
        return transfers.size();
    }

    static int getAccountCount(){
        return accounts.size();
    }

    void displayAllAccounts(){
        for(const auto &account : accounts){
            account->displayAccount();
        }
    }

    void displayAllTransfers(){
        for(const auto &transfer : transfers){
            transfer->displayTransfer();
        }
    }

    std::vector<std::shared_ptr<Account>> getTransfersOfAccount(int accountNumber);

    std::vector<std::shared_ptr<MoneyTransfer>> getTransfersByDate(const std::string& date);

    ~Manager();
};



#endif //MYBANKOPERATIONS_MANAGER_H
