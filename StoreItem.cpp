#include "StoreItem.h"
#include <iostream>
using namespace std;

StoreItem::StoreItem(){
;}

void StoreItem::setStoreItem(string id, string na, string des, string cat, string manu, float sellP, float costP, int unitInS, int unitS, int yearI, int monthI, int dayI)
{
  itemID = id;
  name = na;
  description = des;
  category = cat;
  manufacturer = manu;
  sellPrice = sellP;
  costPrice = costP;
  unitInStore = unitInS;
  unitSold = unitS;
  year = yearI;
  month = monthI;
  day = dayI;
}

void StoreItem::setItemId(string id) { itemID = id; }
void StoreItem::setName(string na) { name = na; }
void StoreItem::setDescription(string des) { description = des; }
void StoreItem::setCategory(string cat) { category = cat; }
void StoreItem::setManufacturer(string manu) { manufacturer = manu; }
void StoreItem::setSellPrice(float sellP) { sellPrice = sellP; }
void StoreItem::setCostPrice(float costP) { costPrice = costP; }
void StoreItem::setUnitInStore(int unitInS) { unitInStore = unitInS; }
void StoreItem::setUnitSold(int unitS) { unitSold = unitS; }
void StoreItem::setYear(int yearI) { year = yearI; }
void StoreItem::setMonth(int monthI) { month = monthI; }
void StoreItem::setDay(int dayI) { day = dayI; }


string StoreItem::getItemId() { return itemID; }
string StoreItem::getName() { return name; }
string StoreItem::getDescription() { return description; }
string StoreItem::getCategory() { return category; }
string StoreItem::getManufacturer() { return manufacturer; }
float StoreItem::getSellPrice() { return sellPrice; }
float StoreItem::getCostPrice() { return costPrice; }
int StoreItem::getUnitInStore() { return unitInStore; }
int StoreItem::getUnitSold() { return unitSold; }
int StoreItem::getYear() { return year; }
int StoreItem::getMonth() { return month; }
int StoreItem::getDay() {return day; }
