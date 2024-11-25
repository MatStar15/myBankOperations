//
// Created by Mat on 05/09/2024.
//

#include "Manager.h"
#include <memory>
#include <iostream>


#define ACCOUNTS_FILE "bankAccounts.txt"
#define TRANSFERS_FILE "transfers.txt"


int Manager::transferCount = 0;
int Manager::accountCount = 0;

std::vector<std::shared_ptr<Account>> Manager::accounts;
std::vector<std::shared_ptr<MoneyTransfer>> Manager::transfers;

Manager* Manager::instance = nullptr;


void Manager::saveAccount(const Account &account) {
    std::ofstream file(ACCOUNTS_FILE, std::ios::app);
    file << account.getAccountNumber() << " " << account.getAccountHolder() << " " << account.getBalance() << std::endl;
    file.close();
//    std::cout << "Account saved" << std::endl;
}

void Manager::saveTransfer(const MoneyTransfer &moneyTransfer) {
    std::ofstream file(TRANSFERS_FILE, std::ios::app);
    file << moneyTransfer.getSenderAccount()->getAccountNumber() << " " << moneyTransfer.getReceiverAccount()->getAccountNumber() << " " << moneyTransfer.getAmount() <<  " " << moneyTransfer.getTransferNumber()<<std::endl;
    file.close();
//    std::cout << "Transfer saved" << std::endl;
}

void Manager::loadAccounts() {
    std::ifstream file(ACCOUNTS_FILE);
    if (file.is_open()) {
        int accountNumber;
        std::string accountHolder;
        double balance;
        while (file >> accountNumber >> accountHolder >> balance) {
            std::shared_ptr<Account> account = std::make_shared<Account>(Account(balance, accountNumber, accountHolder));
        }
        file.close();
    }
}

void Manager::loadTransfers() {
    std::ifstream file(TRANSFERS_FILE);
    if(file.is_open()) {
        int senderAccountNumber, receiverAccountNumber, transferNumber;
        double amount;
        while (file >> senderAccountNumber >> receiverAccountNumber >> amount >> transferNumber) {
            std::shared_ptr<Account> senderAccount = getAccount(senderAccountNumber);
            std::shared_ptr<Account> receiverAccount = getAccount(receiverAccountNumber);
            std::shared_ptr<MoneyTransfer>  moneyTransfer = std::make_shared<MoneyTransfer>(MoneyTransfer(amount, senderAccount, receiverAccount, transferNumber));
        }
        file.close();
    }
}

std::shared_ptr<Account> Manager::getAccount(int accountNumber) {
    for (const auto &account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            return account;
        }
    }
    return nullptr;
}

std::shared_ptr<MoneyTransfer> Manager::getTransfer(int transferNumber) {
    for (const auto &transfer : transfers) {
        if (transfer->getTransferNumber() == transferNumber) {
            return transfer;
        }
    }
    return nullptr;
}

void Manager::saveAllAccounts() {
    for (const auto &account : accounts) {
        saveAccount(*account);
    }
}

void Manager::saveAllTransfers() {
    for (const auto &transfer : transfers) {
        saveTransfer(*transfer);
    }

}

void Manager::addAccount(const std::shared_ptr<Account>& account) {
    accounts.push_back(account);
    accountCount++;
}

void Manager::addTransfer(const std::shared_ptr<MoneyTransfer>& moneyTransfer) {
    transfers.push_back(moneyTransfer);
    transferCount++;
}

void Manager::wipe() {
    std::ofstream ofs;
    ofs.open(ACCOUNTS_FILE, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    ofs.open(TRANSFERS_FILE, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}


void Manager::save() {
    wipe();
    saveAllAccounts();
    saveAllTransfers();
}

Manager::~Manager() {
    instance = nullptr;
    save();
    accounts.clear();
    transfers.clear();
    transferCount = 0;
    accountCount = 0;
}

std::vector<std::shared_ptr<Account>> Manager::getHolderAccounts(const std::string &holderName) {
    std::vector<std::shared_ptr<Account>> holderAccounts;
    for (const auto &account : accounts) {
        if (account->getAccountHolder() == holderName) {
            holderAccounts.push_back(account);
        }
    }
    return holderAccounts;
}

std::vector<std::shared_ptr<MoneyTransfer>> Manager::getHolderSenderTransfers(const int senderAccountNumber) {
    std::vector<std::shared_ptr<MoneyTransfer>> holderSenderTransfers;
    for (const auto &transfer : transfers) {
        if (transfer->getSenderAccount()->getAccountNumber() == senderAccountNumber) {
            holderSenderTransfers.push_back(transfer);
        }
    }
    return holderSenderTransfers;
}

std::vector<std::shared_ptr<MoneyTransfer>> Manager::getHolderReceiverTransfers(const int receiverAccountNumber) {
    std::vector<std::shared_ptr<MoneyTransfer>> holderReceiverTransfers;
    for (const auto &transfer : transfers) {
        if (transfer->getReceiverAccount()->getAccountNumber() == receiverAccountNumber) {
            holderReceiverTransfers.push_back(transfer);
        }
    }
    return holderReceiverTransfers;
}

