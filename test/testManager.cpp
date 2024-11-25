//
// Created by Mat on 25/11/2024.
//

#include "gtest/gtest.h"
#include "..\Manager.h"
#include <memory>

std::string NAME2 = "Jon_Doe";

class ManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        Manager::wipe();
        auto account1 = std::make_shared<Account>(200.0, "test1");
        auto account2 = std::make_shared<Account>(100.0, "test2");
        auto account3 = std::make_shared<Account>(100.0, "test3");
    }

    void TearDown() override {
        delete Manager::getInstance();
        Manager::wipe();
    }
};

TEST_F(ManagerTest, AddAccountIncreasesAccountCount) {
    ASSERT_EQ(Manager::getAccountCount(), 3);
}

TEST_F(ManagerTest, AddTransferIncreasesTransferCount) {
    auto transfer = std::make_shared<MoneyTransfer>(50.0, 2, 1);
    ASSERT_EQ(Manager::getTransferCount(), 1);
}

TEST_F(ManagerTest, GetAccountReturnsCorrectAccount) {
    auto account = std::make_shared<Account>(100.0, NAME2);
    auto retrievedAccount = Manager::getAccount(account->getAccountNumber());
    ASSERT_EQ(retrievedAccount->getAccountHolder(), NAME2);
}

TEST_F(ManagerTest, GetTransferReturnsCorrectTransfer) {
    auto transfer = std::make_shared<MoneyTransfer>(50.0, 2, 1);
    auto retrievedTransfer = Manager::getTransfer(transfer->getTransferNumber());
    ASSERT_EQ(*retrievedTransfer,*transfer);
}

TEST_F(ManagerTest, GetHolderAccountsReturnsCorrectAccounts) {
    auto account2 = std::make_shared<Account>(200.0, NAME2);
    auto account1 = std::make_shared<Account>(100.0, NAME2);
    auto accounts = Manager::getHolderAccounts(NAME2);
    ASSERT_EQ(accounts.size(), 2);
}

TEST_F(ManagerTest, GetHolderSenderTransfersReturnsCorrectTransfers) {
    auto transfer1 = std::make_shared<MoneyTransfer>(50.0, 1, 2);
    auto transfer2 = std::make_shared<MoneyTransfer>(100.0, 1, 3);
    auto transfers = Manager::getHolderSenderTransfers(1);
    ASSERT_EQ(transfers.size(), 2);
}

TEST_F(ManagerTest, GetHolderReceiverTransfersReturnsCorrectTransfers) {
    auto transfer1 = std::make_shared<MoneyTransfer>(50.0, 1, 2);
    auto transfer2 = std::make_shared<MoneyTransfer>(100.0, 3, 2);
    auto transfers = Manager::getHolderReceiverTransfers(2);
    ASSERT_EQ(transfers.size(), 2);
}

/// Read and write tests

TEST_F(ManagerTest, LoadAccountsSuccessfully) {
    Manager::loadAccounts();
    ASSERT_EQ(Manager::getAccountCount(), 3);
}


TEST_F(ManagerTest, LoadTransfersSuccessfully) {
    Manager::loadTransfers();
    ASSERT_EQ(Manager::getTransferCount(), 0);
}


TEST_F(ManagerTest, SaveAccountsSuccessfully) {
    auto account = std::make_shared<Account>(100.0, NAME2);

    delete Manager::getInstance();
    Manager::getInstance();


    ASSERT_EQ(Manager::getAccountCount(), 4);
    auto retrievedAccount = Manager::getAccount(account->getAccountNumber());
    ASSERT_EQ( retrievedAccount->getAccountNumber(), account->getAccountNumber()); ///FIXME: dereferencing retrievedAccount and account causes build error
}

TEST_F(ManagerTest, SaveTransfersSuccessfully) {
    auto transfer = std::make_shared<MoneyTransfer>(50.0, 1, 2);

    delete Manager::getInstance();
    Manager::getInstance();


    ASSERT_EQ(Manager::getTransferCount(), 1);
    auto retrievedTransfer = Manager::getTransfer(transfer->getTransferNumber());
    ASSERT_EQ(retrievedTransfer->getTransferNumber(), transfer->getTransferNumber());
}
