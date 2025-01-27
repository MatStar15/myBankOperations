//
// Created by Mat on 04/09/2024.
//

#include "Account.h"
#include "MoneyTransfer.h"
#include "Manager.h"
#include <iostream>
#include <sstream>
#include <memory>


Account::Account(double balance, int accountNumber, std::string accountHolder): balance(balance), accountNumber(accountNumber),
                                                                                accountHolder(std::move(accountHolder)) {
    if(balance < 0) {
        throw std::invalid_argument("Balance cannot be negative");
    }

    Manager::addAccount(std::make_shared<Account>(*this));
}


Account::Account(double balance, std::string accountHolder) : Account(balance, Manager::getAccountCount() + 1, std::move(accountHolder)) {}



void Account::transfer(const std::shared_ptr<Account>& account, double amount, const std::string& reason, std::string date)
{
    if (amount < 0) {
        throw std::invalid_argument("Amount must be positive");
    }
    if (account == nullptr) {
        throw std::invalid_argument("Invalid Receiver account");
    }

    if (balance >= amount) {
        balance -= amount;
        account->deposit(amount);


        std::shared_ptr<MoneyTransfer> transfer = std::make_shared<MoneyTransfer>(amount,date, std::make_shared<Account>(*this), account, reason);

    } else {
        throw std::invalid_argument("Insufficient funds");
    }
}

void Account::displayAccount() const {
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}


