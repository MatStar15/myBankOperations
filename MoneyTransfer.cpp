//
// Created by Mat on 04/09/2024.
//

#include "MoneyTransfer.h"
#include "Manager.h"
#include <iostream>


MoneyTransfer::MoneyTransfer(double amount, std::shared_ptr<Account> senAccount,
                             std::shared_ptr<Account> recAccount, int transferNumber) : amount(amount), senderAccount(std::move(senAccount)), receiverAccount(std::move(recAccount)), transferNumber(transferNumber) {

    if(senderAccount == nullptr) {
        throw std::invalid_argument("Invalid Sender account");
    }

    if(receiverAccount == nullptr) {
        throw std::invalid_argument("Invalid Receiver account");
    }

    Manager::addTransfer(std::make_shared<MoneyTransfer>(*this));

}

MoneyTransfer::MoneyTransfer(double amount, std::shared_ptr<Account> senAccount,
                             std::shared_ptr<Account> recAccount) : MoneyTransfer(amount, senAccount, recAccount, Manager::getTransferCount() + 1) {};

MoneyTransfer::MoneyTransfer(double amount, int senderAccount, int receiverAccount):
        MoneyTransfer(amount, Manager::getAccount(senderAccount), Manager::getAccount(receiverAccount), Manager::getAccountCount() + 1) {}



void MoneyTransfer::displayTransfer() const {
    std::cout << "Amount: " << amount << std::endl;
    std::cout << "Sender Account Number: " << senderAccount->getAccountNumber() << std::endl;
    std::cout << "Receiver Account Number: " << receiverAccount->getAccountNumber() << std::endl;
}



