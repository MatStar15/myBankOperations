//
// Created by Mat on 05/09/2024.
//

#include "Manager.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


const std::string ACCOUNTS_FILE = "bankAccounts.txt";
const std::string TRANSFERS_FILE = "transfers.txt";


std::vector<std::shared_ptr<Account>> Manager::accounts;
std::vector<std::shared_ptr<MoneyTransfer>> Manager::transfers;

Manager* Manager::instance = nullptr;


void Manager::saveAccount(const Account &account) {
    std::ofstream file(ACCOUNTS_FILE, std::ios::app);
    file << account.getAccountNumber() << " " << account.getAccountHolder() << " " << account.getBalance() << std::endl;
    file.close();
}

void Manager::saveTransfer(const MoneyTransfer &moneyTransfer) {
    std::ofstream file(TRANSFERS_FILE, std::ios::app);
    file << moneyTransfer.getSenderAccount()->getAccountNumber()
    << " " << moneyTransfer.getReceiverAccount()->getAccountNumber()
    << " " << moneyTransfer.getAmount()
    << " " << moneyTransfer.getTransferDate()
    <<  " " << moneyTransfer.getTransferNumber()<<std::endl;
    file << moneyTransfer.getReason() << std::endl;
    file.close();
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

    if (!file.is_open()) {
        std::ofstream ofs;
        ofs.open(TRANSFERS_FILE, std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        file.open(TRANSFERS_FILE);

        if (!file.is_open())
        {
            throw std::runtime_error("Unable to open or create transfers file");
        }

    }

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);

            int senderAccountNumber, receiverAccountNumber, transferNumber;
            double amount;
            std::string transferDate, reason;

        if (iss >> senderAccountNumber >> receiverAccountNumber >> amount >> transferDate >>transferNumber) // Parse first part of the transfer
        {
            if (std::getline(file, line)) // Parse second part of the transfer, aka the reason
            {
                std::shared_ptr<Account> senderAccount = getAccount(senderAccountNumber);
                std::shared_ptr<Account> receiverAccount = getAccount(receiverAccountNumber);
                std::shared_ptr<MoneyTransfer>  moneyTransfer = std::make_shared<MoneyTransfer>(
                    MoneyTransfer(amount, transferDate, line, senderAccount, receiverAccount, transferNumber));
            }else
            {
                throw std::runtime_error("Unable to parse transfer reason");
            }

        }else
        {
            throw std::runtime_error("Unable to parse transfer");
        }
    }
    file.close();
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
}

void Manager::addTransfer(const std::shared_ptr<MoneyTransfer>& moneyTransfer) {
    transfers.push_back(moneyTransfer);
}

void Manager::removeTransfer(const std::shared_ptr<MoneyTransfer>& moneyTransfer)
{
    for (auto it = transfers.begin(); it != transfers.end(); ++it) {
        if (*it == moneyTransfer) {
            transfers.erase(it); // Delete the transfer from the manager

            // Reverse the transfer:
            moneyTransfer->getReceiverAccount()->withdraw(moneyTransfer->getAmount());
            moneyTransfer->getSenderAccount()->deposit(moneyTransfer->getAmount());
            break;
        }
    }
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

std::vector<std::shared_ptr<Account>> Manager::getTransfersOfAccount(int accountNumber)
{
    std::vector<std::shared_ptr<Account>> found = {};
    for (const auto &account : accounts) {
        if (account->getAccountNumber() == accountNumber) {
            for (const auto &transfer : transfers)
            {
                if (transfer->getSenderAccount()->getAccountNumber() == accountNumber || transfer->getReceiverAccount()->getAccountNumber() == accountNumber) {
                    found.push_back(account);
                }
            }
        }
    }
    return found;
}

std::vector<std::shared_ptr<MoneyTransfer>> Manager::getTransfersByDate(const std::string& date)
{
    std::vector<std::shared_ptr<MoneyTransfer>> found = {};
    for (const auto &transfer : transfers) {
        if (transfer->getTransferDate() == date) {
            found.push_back(transfer);
        }
    }
    return found;
}

Manager::~Manager() {
    save();
    accounts.clear();
    transfers.clear();
    instance = nullptr;
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

