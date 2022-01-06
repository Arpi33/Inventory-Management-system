#ifndef STOREITEM_H
#define STOREITEM_H
#include <iostream>
using namespace std;

class StoreItem
{
  private:
    string itemID, name, description, category, manufacturer;
    float sellPrice, costPrice;
    int unitInStore, unitSold, year, month, day;

  public:
    StoreItem();
    ~StoreItem(){};
    void setStoreItem(string itemID, string name, string description, string category, string manufacturer, float sellPrice, float costPrice, int unitInStore, int unitSold, int year, int month, int day);
    void setItemId(string itemID);
    void setName(string name);
    void setDescription(string description);
    void setCategory(string category);
    void setManufacturer(string manufacturer);
    void setSellPrice(float sellPrice);
    void setCostPrice(float costPrice);
    void setUnitInStore(int unitInStore);
    void setUnitSold(int unitSold);
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    string getItemId();
    string getName();
    string getDescription();
    string getCategory();
    string getManufacturer();
    float getSellPrice();
    float getCostPrice();
    int getUnitInStore();
    int getUnitSold();
    int getYear();
    int getMonth();
    int getDay();
};
#endif
