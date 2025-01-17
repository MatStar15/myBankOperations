//
// Created by Mat on 04/09/2024.
//

#ifndef MYBANDOPERATIONS_ACCOUNT_H
#define MYBANDOPERATIONS_ACCOUNT_H

#include <string>
#include <memory>
#include <stdexcept>

class Manager;


class Account {
private:
    double balance;
    int accountNumber;
    std::string accountHolder;
public:
    // Constructor when the account is created
    Account(double balance, std::string accountHolder);

    // Constructor when the account is loaded from disk
    Account(double balance, int accountNumber, std::string accountHolder);

    // Copy constructor
    explicit Account(std::shared_ptr<Account> account): balance(account->getBalance()), accountNumber(account->getAccountNumber()), accountHolder(account->getAccountHolder()){}


    double getBalance() const{
        return balance;
    }

    int getAccountNumber() const{
        return accountNumber;
    }

    const std::string &getAccountHolder() const{
        return accountHolder;
    }

    void setAccountHolder(const std::string &newAccountHolder){
        Account::accountHolder = newAccountHolder;
    }

    void deposit(double amount){
        if(amount < 0){
            throw std::invalid_argument("Amount must be positive");
        }
        balance += amount;
    }

    void withdraw(double amount){
        if(amount < 0){
            throw std::invalid_argument("Amount must be positive");
        }
        if(amount > balance){
            throw std::invalid_argument("Insufficient funds");
        }
        balance -= amount;
    }

    void transfer(const std::shared_ptr<Account>& account, double amount, const std::string& reason = "", std::string date= "");

    void displayAccount() const;
};


#endif //MYBANDOPERATIONS_ACCOUNT_H
