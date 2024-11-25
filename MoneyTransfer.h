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
    std::shared_ptr<Account> senderAccount;
    std::shared_ptr<Account> receiverAccount;
public:
    bool operator==(const MoneyTransfer &rhs) const {
        return amount == rhs.amount &&
               transferNumber == rhs.transferNumber &&
               senderAccount == rhs.senderAccount &&
               receiverAccount == rhs.receiverAccount;
    }

    // Constructor when the transfer is loaded from disk
    explicit MoneyTransfer(double amount, std::shared_ptr<Account> senderAccount, std::shared_ptr<Account> receiverAccount, int transferNumber);

    // Constructor when the transfer is made
    explicit MoneyTransfer(double amount, std::shared_ptr<Account> senderAccount, std::shared_ptr<Account> receiverAccount);

    explicit MoneyTransfer(double amount, int senderAccount, int receiverAccount);





    MoneyTransfer() = delete;

    double getAmount() const{
        return amount;
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
