//
// Created by Mat on 07/10/2024.
//

#include <iostream>
#include "Manager.h"

void createAccount(){
    double balance;
    std::string accountHolder;
    std::cout << "Enter the account holder name: " << std::endl;
    std::cin >> accountHolder;
    std::cout << "Enter the initial balance: " << std::endl;
    std::cin >> balance;
    try {
        std::make_shared<Account>(balance, accountHolder);
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl << "Account not created, try again" << std::endl;
    }

}

void createTransfer(){
    int senderAccountNumber, receiverAccountNumber;
    double amount;
    std::cout << "Enter the sender account number: " << std::endl;
    std::cin >> senderAccountNumber;
    std::cout << "Enter the receiver account number: " << std::endl;
    std::cin >> receiverAccountNumber;
    std::cout << "Enter the amount: " << std::endl;
    std::cin >> amount;
    try {
        std::shared_ptr<Account> senderAccount = Manager::getAccount(senderAccountNumber);

        if (senderAccount == nullptr) {
            throw std::invalid_argument("Invalid Sender account");
        }

        std::shared_ptr<Account> receiverAccount = Manager::getAccount(receiverAccountNumber);

        if (receiverAccount == nullptr) {
            throw std::invalid_argument("Invalid Receiver account");
        }

        Manager::getAccount(senderAccountNumber)->transfer(Manager::getAccount(receiverAccountNumber), amount);
    }

    catch (std::exception &e){
        std::cout << e.what() << std::endl << "Transfer not created, try again" << std::endl;
    }
}

void searchAccountByHolder () {
    std::string holderName;
    std::cout << "Enter the account holder name: " << std::endl;
    std::cin >> holderName;
    std::vector<std::shared_ptr<Account>> accounts = Manager::getHolderAccounts(holderName);
    if (accounts.empty()) {
        std::cout << "No accounts found for " << holderName << std::endl;
    } else {
        for (auto &account: accounts) {
            std::cout << "Account number: " << account->getAccountNumber() << " Balance: " << account->getBalance()
                      << std::endl;
        }
    }
}

void searchOutgoingTransfersByAccountNumber (int accountNumber) {
    std::vector<std::shared_ptr<MoneyTransfer>> transfers = Manager::getHolderSenderTransfers(accountNumber);
    if(transfers.empty()){
        std::cout << "No transfers found for account number " << accountNumber << std::endl;
    } else {
        for(auto &transfer: transfers){
            transfer->displayTransfer();
        }
    }
}

void searchIncomingTransfersByAccountNumber (int accountNumber) {
    std::vector<std::shared_ptr<MoneyTransfer>> transfers = Manager::getHolderReceiverTransfers(accountNumber);
    if (transfers.empty()) {
        std::cout << "No transfers found for account number " << accountNumber << std::endl;
    } else {
        for (auto &transfer: transfers) {
            transfer->displayTransfer();
        }
    }
}

void searchTransfersByAccountNumber () {
    int accountNumber;
    std::cout << "Enter the account number: " << std::endl;
    std::cin >> accountNumber;

    int action;
    std::cout << "Select an action: " << std::endl;
    std::cout << "[1] Outgoing transfers" << std::endl;
    std::cout << "[2] Incoming transfers" << std::endl;
    std::cin >> action;

    switch (action) {
        case 1:
            searchOutgoingTransfersByAccountNumber(accountNumber);
            break;
        case 2:
            searchIncomingTransfersByAccountNumber(accountNumber);
            break;
        default:
            std::cout << "Invalid action" << std::endl;
    }
}

void deposit(){
    int accountNumber;
    double amount;
    std::cout << "Enter the account number: " << std::endl;
    std::cin >> accountNumber;
    std::cout << "Enter the amount: " << std::endl;
    std::cin >> amount;
    try {
        std::shared_ptr<Account> account = Manager::getAccount(accountNumber);
        if (account == nullptr) {
            throw std::invalid_argument("Invalid account");
        }
        account->deposit(amount);
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl << "Deposit was not possible, try again" << std::endl;
    }
}

void withdraw(){
    int accountNumber;
    double amount;
    std::cout << "Enter the account number: " << std::endl;
    std::cin >> accountNumber;
    std::cout << "Enter the amount: " << std::endl;
    std::cin >> amount;
    try {
        std::shared_ptr<Account> account = Manager::getAccount(accountNumber);
        if (account == nullptr) {
            throw std::invalid_argument("Invalid account");
        }
        account->withdraw(amount);
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl << "Withdraw was not possible, try again" << std::endl;
    }
}


int main(){
    Manager* manager = Manager::getInstance();

    std::string answer;
    std::cout << "start new sessions? [y/n]" << std::endl;
    std::cin >> answer;
    if(answer == "y" || answer == "Y"){
        manager->wipe();
    }


    while(true){
        std::cout << "Select an action: " << std::endl;
        std::cout << "[1] Create Account" << std::endl;
        std::cout << "[2] Create Transfer" << std::endl;
        std::cout << "[3] Display all accounts" << std::endl;
        std::cout << "[4] Display all transfers" << std::endl;
        std::cout << "[5] Search for an account" << std::endl;
        std::cout << "[6] Show transfers involving an account" << std::endl;
        std::cout << "[7] Deposit" << std::endl;
        std::cout << "[8] Withdraw" << std::endl;
        std::cout << "[9] Exit" << std::endl;

        int action;
        std::cin >> action;
        switch(action){
            case 1:
                createAccount();
                break;
            case 2:
                createTransfer();
                break;
            case 3:
                Manager::displayAllAccounts();
                break;
            case 4:
                Manager::displayAllTransfers();
                break;
            case 5:
                searchAccountByHolder();
                break;
            case 6:
                searchTransfersByAccountNumber();
                break;
            case 7:
                deposit();
                break;
            case 8:
                withdraw();
                break;
            case 9:
                delete manager;
                return 0;
            default:
                std::cout << "Invalid action" << std::endl;
        }
    }

}