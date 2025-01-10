//
// Created by Mat on 04/09/2024.
//

#include "MoneyTransfer.h"
#include "Manager.h"
#include <iostream>
#include <utility>
#include <ctime>
#include <iomanip>

// Constructor when the transfer is loaded from disk
MoneyTransfer::MoneyTransfer(double amount, std::string date,std::string reason, std::shared_ptr<Account> senAccount,
                             std::shared_ptr<Account> recAccount, int transferNumber) : amount(amount),transferDate(std::move(date)),reason(std::move(reason)), senderAccount(std::move(senAccount)), receiverAccount(std::move(recAccount)), transferNumber(transferNumber) {

    if(senderAccount == nullptr) {
        throw std::invalid_argument("Invalid Sender account");
    }

    if(receiverAccount == nullptr) {
        throw std::invalid_argument("Invalid Receiver account");
    }

    if (amount < 0) {
        throw std::invalid_argument("Amount must be positive");
    }

    Manager::addTransfer(std::make_shared<MoneyTransfer>(*this));
}


// Constructor when the transfer is made
MoneyTransfer::MoneyTransfer(double amount, std::string date, std::shared_ptr<Account> senAccount,
                             std::shared_ptr<Account> recAccount, std::string reason) : MoneyTransfer(amount,std::move(date), std::move(reason), std::move(senAccount), std::move(recAccount), Manager::getTransferCount() + 1) {};

std::string currentTimeAsString()
{
    time_t t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y--%H-%M-%S");
    std::string str = oss.str();

    return str;
}

// If no Transfer date is provided, the current date is used
MoneyTransfer::MoneyTransfer(double amnt, std::shared_ptr<Account> senAccount,
    std::shared_ptr<Account> recAccount, const std::string& r) :
    MoneyTransfer(amnt, currentTimeAsString(), r, std::move(senAccount),
        std::move(recAccount),Manager::getTransferCount() + 1 ) {}

// Mainly for testing purposes
MoneyTransfer::MoneyTransfer(double amount, int senderAccountID, int receiverAccountID ):
        MoneyTransfer(amount, Manager::getAccount(senderAccountID), Manager::getAccount(receiverAccountID),
            "Reason") {}


MoneyTransfer::MoneyTransfer(double amount, std::string date, std::string reason, int senderAccountID,int receiverAccountID) :
    MoneyTransfer(amount, std::move(date), std::move(reason),
    Manager::getAccount(senderAccountID), Manager::getAccount(receiverAccountID),
    Manager::getTransferCount() + 1){}


void MoneyTransfer::displayTransfer() const {
    std::cout << "Transfer Number: " << transferNumber << std::endl;
    std::cout << "Amount: " << amount << std::endl;
    std::cout << "Date: " << transferDate << std::endl;
    std::cout << "Sender Account Number: " << senderAccount->getAccountNumber() << std::endl;
    std::cout << "Receiver Account Number: " << receiverAccount->getAccountNumber() << std::endl;
    std::cout << "Reason: " << reason << std::endl;
}



