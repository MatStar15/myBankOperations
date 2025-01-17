//
// Created by Mat on 04/09/2024.
//

#ifndef MYBANKOPERATIONS_MONEYTRANSFER_H
#define MYBANKOPERATIONS_MONEYTRANSFER_H

#include <memory>
#include <utility>
#include "Account.h"

class MoneyTransfer {
private:
    double amount;
    int transferNumber;
    std::string reason;
    std::string transferDate;
    std::shared_ptr<Account> senderAccount;
    std::shared_ptr<Account> receiverAccount;
public:
    bool operator==(const MoneyTransfer &rhs) const {
        return amount == rhs.amount &&
               transferNumber == rhs.transferNumber &&
               senderAccount->getAccountNumber() == rhs.senderAccount->getAccountNumber() &&
               receiverAccount->getAccountNumber() == rhs.receiverAccount->getAccountNumber() &&
               reason == rhs.reason &&
               transferDate == rhs.transferDate;
    }

    // Constructor when the transfer is loaded from disk
    MoneyTransfer(double amount, std::string date,std::string reason, std::shared_ptr<Account> senAccount,
                             std::shared_ptr<Account> recAccount, int transferNumber);

    // Constructor when the transfer is made
    MoneyTransfer(double amount, std::string date, std::shared_ptr<Account> senderAccount, std::shared_ptr<Account> receiverAccount, std::string reason = " ");
    MoneyTransfer(double amnt, std::shared_ptr<Account> senAccount,std::shared_ptr<Account> recAccount, const std::string& r = " ");

    // Mainly for testing purposes
    MoneyTransfer(double amount, int senderAccountID, int receiverAccountID);

    MoneyTransfer(double amount,std::string date, std::string reason, int senderAccountID, int receiverAccountID);

    MoneyTransfer() = delete;

    double getAmount() const{
        return amount;
    }

    std::string getTransferDate() const{
        return transferDate;
    }

    std::string getReason() const{
        return reason;
    }

    std::shared_ptr<Account> getSenderAccount() const{
        return senderAccount;
    }

    std::shared_ptr<Account> getReceiverAccount() const{
        return receiverAccount;
    }

    int getTransferNumber() const{
        return transferNumber;
    }

    void displayTransfer() const;
};


#endif //MYBANKOPERATIONS_MONEYTRANSFER_H
