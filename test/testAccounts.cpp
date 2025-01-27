//
// Created by Mat on 25/11/2024.
//

#include "MoneyTransfer.h"
#include "gtest/gtest.h"
#include "../Account.h"

std::string NAME = "AccountTest";

class AccountTest : public ::testing::Test {
protected:
    std::shared_ptr<Account> account;

    void SetUp() override {
        account = std::make_shared<Account>(100.0, NAME);
    }
};

TEST_F(AccountTest, DepositIncreasesBalance) {
    account->deposit(50.0);
    ASSERT_EQ(account->getBalance(), 150.0);
}

TEST_F(AccountTest, DepositNegativeAmountThrowsException) {
    ASSERT_THROW(account->deposit(-50.0), std::invalid_argument);
}

TEST_F(AccountTest, WithdrawDecreasesBalance) {
    account->withdraw(50.0);
    ASSERT_EQ(account->getBalance(), 50.0);
}

TEST_F(AccountTest, WithdrawNegativeAmountThrowsException) {
    ASSERT_THROW(account->withdraw(-50.0), std::invalid_argument);
}

TEST_F(AccountTest, WithdrawMoreThanBalanceThrowsException) {
    ASSERT_THROW(account->withdraw(150.0), std::invalid_argument);
}

TEST_F(AccountTest, TransferFundsSuccessfully) {
    auto targetAccount = std::make_shared<Account>(50.0, NAME);
    account->transfer(targetAccount, 50.0);
    ASSERT_EQ(account->getBalance(), 50.0);
    ASSERT_EQ(targetAccount->getBalance(), 100.0);
}

TEST_F(AccountTest, TransferNegativeAmountThrowsException) {
    auto targetAccount = std::make_shared<Account>(50.0, NAME);
    ASSERT_THROW(account->transfer(targetAccount, -50.0), std::invalid_argument);
}

TEST_F(AccountTest, TransferMoreThanBalanceThrowsException) {
    auto targetAccount = std::make_shared<Account>(50.0, NAME);
    ASSERT_THROW(account->transfer(targetAccount, 150.0), std::invalid_argument);
}

TEST_F(AccountTest, TransferToNullptrThrowsException) {
    ASSERT_THROW(account->transfer(nullptr, 50.0), std::invalid_argument);
}

TEST_F(AccountTest, InvalidTransferDateThrowsException) {
    auto targetAccount = std::make_shared<Account>(50.0, NAME);
    ASSERT_THROW(MoneyTransfer(50, "Invalid Date", account, targetAccount), std::invalid_argument);
}