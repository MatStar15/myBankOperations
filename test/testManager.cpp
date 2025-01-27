//
// Created by Mat on 25/11/2024.
//

#include "gtest/gtest.h"
#include "../Manager.h"
#include <memory>


std::string NAME2 = "Jon_Doe";

class ManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        Manager* manager = Manager::getInstance();
        manager->wipe();
        auto account1 = std::make_shared<Account>(200.0, "test1");
        auto account2 = std::make_shared<Account>(100.0, "test2");
        auto account3 = std::make_shared<Account>(100.0, "test3");
    }

    void TearDown() override {
        Manager* manager = Manager::getInstance();
        delete Manager::getInstance();
        manager->wipe();
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
    Manager* manager = Manager::getInstance();

    auto account2 = std::make_shared<Account>(200.0, NAME2);
    auto account1 = std::make_shared<Account>(100.0, NAME2);
    auto found_accounts = manager->getHolderAccounts(NAME2);
    ASSERT_EQ(found_accounts.size(), 2);
}

TEST_F(ManagerTest, GetHolderSenderTransfersReturnsCorrectTransfers) {
    Manager* manager = Manager::getInstance();
    auto transfer1 = std::make_shared<MoneyTransfer>(50.0, 1, 2);
    auto transfer2 = std::make_shared<MoneyTransfer>(100.0, 1, 3);
    auto found_transfers = manager->getHolderSenderTransfers(1);
    ASSERT_EQ(found_transfers.size(), 2);
}

TEST_F(ManagerTest, GetHolderReceiverTransfersReturnsCorrectTransfers) {
    Manager* manager = Manager::getInstance();
    auto transfer1 = std::make_shared<MoneyTransfer>(50.0, 1, 2);
    auto transfer2 = std::make_shared<MoneyTransfer>(100.0, 3, 2);
    auto found_transfers = manager->getHolderReceiverTransfers(2);
    ASSERT_EQ(found_transfers.size(), 2);
}

/// Read and write tests

TEST_F(ManagerTest, LoadAccountsSuccessfully) {
    Manager* manager = Manager::getInstance();
    manager->loadAccounts();
    ASSERT_EQ(Manager::getAccountCount(), 3);
}


TEST_F(ManagerTest, LoadTransfersSuccessfully) {
    Manager* manager = Manager::getInstance();
    manager->loadTransfers();
    ASSERT_EQ(Manager::getTransferCount(), 0);
}


TEST_F(ManagerTest, SaveAccountsSuccessfully) {
    auto account = std::make_shared<Account>(100.0, NAME2);

    delete Manager::getInstance();
    Manager::getInstance();


    ASSERT_EQ(Manager::getAccountCount(), 4);
    auto retrievedAccount = Manager::getAccount(account->getAccountNumber());
    ASSERT_EQ( retrievedAccount->getAccountNumber(), account->getAccountNumber());
}

TEST_F(ManagerTest, SaveTransfersSuccessfully) {
    auto transfer = std::make_shared<MoneyTransfer>(50.0, 1, 2);

    delete Manager::getInstance();
    Manager::getInstance();

    ASSERT_EQ(Manager::getTransferCount(), 1);
    auto retrievedTransfer = Manager::getTransfer(transfer->getTransferNumber());

    ASSERT_EQ(*retrievedTransfer, *transfer);
    ASSERT_EQ(retrievedTransfer->getTransferNumber(), transfer->getTransferNumber());
    ASSERT_EQ(retrievedTransfer->getAmount(), transfer->getAmount());
    ASSERT_EQ(retrievedTransfer->getSenderAccount()->getAccountNumber(), transfer->getSenderAccount()->getAccountNumber());
    ASSERT_EQ(retrievedTransfer->getReceiverAccount()->getAccountNumber(), transfer->getReceiverAccount()->getAccountNumber());
    ASSERT_EQ(retrievedTransfer->getReason(), transfer->getReason());
    ASSERT_EQ(retrievedTransfer->getTransferDate(), transfer->getTransferDate());

}

TEST_F(ManagerTest, searchTransfersByDate)
{
    Manager* manager = Manager::getInstance();
    auto transfer1 = std::make_shared<MoneyTransfer>(50.0, 1, 2);
    auto transfer2 = std::make_shared<MoneyTransfer>(100.0, 3, 2);


    auto found_transfers = manager->getTransfersByDate(transfer1->getTransferDate());
    ASSERT_EQ(found_transfers.size(), 2);
}