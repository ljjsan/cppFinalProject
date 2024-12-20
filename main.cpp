/*
==============================================================================
   File Name          : main.cpp
   Student Name       : JJ Li
   Last Modified Date : 11/1/2024
   Description        : 
     This program simulates a delivery order system where users can place 
     boba and food orders. It applies discounts based on the user's account 
     status (Owner, VIP, or Regular).

   Functions:
     - applyDiscount: Applies discounts to a delivery order based on the 
       user's account status.

   Classes:
     - DeliveryOrder: Base class for handling delivery orders.
     - BobaOrder: Derived class for managing boba orders.
     - FoodOrder: Derived class for managing food orders.
     - Account: Represents a user account with status and related methods.

============================================================================== 
*/

#include <iostream>
#include <iomanip>

#include "DeliveryOrder.h"
#include "BobaOrder.h"
#include "FoodOrder.h"
#include "Account.h"
#include "InvalidInput.h"


// Check account status and apply the corresponding discount
float applyDiscount(DeliveryOrder* deliveryOrder, const Account& account)
{
    if (account.getStatus() == "Owner")
        return 0.1 * (*deliveryOrder).getTotalBalance();
    else if (account.getStatus() == "VIP")
        return (*deliveryOrder).VIPdiscount() * (*deliveryOrder).getTotalBalance();
    else
        return (*deliveryOrder).getTotalBalance();
}


int main()
{
    // Set cout to print with fixed-point notation and 2 decimal places
    std::cout << std::fixed << std::setprecision(2);

    // Creating account instances for different users
    const Account stuartAccount("Stuart", "Owner");
    Account kevinAccount("Kevin", "VIP");
    Account bobAccount("Bob");

    DeliveryOrder* deliveryOrder = nullptr;   // Pointer to DeliveryOrder object

    // Section: Kevin places a boba order
    std::cout << "Kevin is placing an order.\n";
    BobaOrder kevinDrinkOrder("Kevin", "04/20/2024", "123-456-0000", 10.4, "M Tea");

    try
    {
        // Add drinks to Kevin's order
        kevinDrinkOrder.addDrink("Green Tea Latte");
        kevinDrinkOrder.addDrink("Brown Sugar Pearl Milk", false);
        kevinDrinkOrder.addDrink("Brown Sugar Boba Milk", false, 2);
        kevinDrinkOrder.addDrink("Iron Goddess");
    }
    catch(const InvalidInput & e)
    {
        e.reason();
        std::cout << "Not serving requested drinks. Drink order ignored.\n\n";
    }
    
    // Print receipt and total balance for Kevin's order
    kevinDrinkOrder.receipt();
    std::cout << "Balance: $" << kevinDrinkOrder.getTotalBalance() << std::endl;

    // Apply discount to Kevin's order and print the discounted balance
    deliveryOrder = &kevinDrinkOrder;
    std::cout << "Discounted Balance: $" << applyDiscount(deliveryOrder, kevinAccount) << std::endl;
    std::cout << "\n\n";

    // Section: Stuart places a food order
    std::cout << "Stuart is placing order.\n";
    FoodOrder stuartFoodOrder("Stuart", "04/20/2024", "123-456-1111", 25.5, "Tavern Green");

    try
    {
        // Add food items to Stuart's order
        stuartFoodOrder.addFood("Thick Cauliflower Steaks", 1, true);
        stuartFoodOrder.addFood("Organic Scottish Salmon", 0, false);
        stuartFoodOrder.addFood("Rack of Lamb", 0, true);
        //stuartFoodOrder.addFood("fda", 0, true);
    }
    catch(const InvalidInput & e)
    {
      e.reason();
      std::cout << "Not serving requested food. Food order ignored.\n\n";
    }
      
    // Print receipt and total balance for Stuart's order
    stuartFoodOrder.receipt();
    std::cout << "Balance: $" << stuartFoodOrder.getTotalBalance() << std::endl;

    // Apply discount to Stuart's order and print the discounted balance
    deliveryOrder = &stuartFoodOrder;
    std::cout << "Discounted Balance: $" << applyDiscount(deliveryOrder, stuartAccount) << std::endl;
    std::cout << "\n\n";

    // Section: Bob checks his ability to order the same items as Stuart
    std::cout << "Bob decided to log in to his account and see whether he can afford ordering the same order as Stuart.\n";
    stuartFoodOrder.receipt();
    std::cout << "Balance: $" << stuartFoodOrder.getTotalBalance() << std::endl;
    std::cout << "Discounted Balance: $" << applyDiscount(deliveryOrder, bobAccount) << std::endl;
    std::cout << "Bob upset, cancelling order :(\n\n";

    // Display total number of orders placed
    std::cout << "Total order placed: " << DeliveryOrder::getOrderCount() << "\n\n";
    
    return 0;
}
