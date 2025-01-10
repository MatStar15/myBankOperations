//
// Created by Mat on 04/09/2024.
//

#include "Account.h"
#include "MoneyTransfer.h"
#include "Manager.h"
#include <iostream>
#include <memory>


Account::Account(double balance, int accountNumber, std::string accountHolder): balance(balance), accountNumber(accountNumber),
                                                                                accountHolder(std::move(accountHolder)) {
    Manager::addAccount(std::make_shared<Account>(*this));

    if(balance < 0) {
        throw std::invalid_argument("Balance cannot be negative");
    }
}


Account::Account(double balance, std::string accountHolder) : Account(balance, Manager::getAccountCount() + 1, std::move(accountHolder)) {}




void Account::transfer(const std::shared_ptr<Account>& account, double amount, const std::string& reason) {
    if (balance >= amount) {
        balance -= amount;
        account->deposit(amount);


       std::shared_ptr<MoneyTransfer> transfer = std::make_shared<MoneyTransfer>(amount, std::make_shared<Account>(*this), account, reason);

    } else {
        throw std::invalid_argument("Insufficient funds");
    }
}

void Account::displayAccount() const {
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}


