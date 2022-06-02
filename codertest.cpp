#include "coder.h"
#include "codelist.h"
#include "string5.h"
#include "filehandler.h"
#include "xorcode.h"
#include "morsecode.h"

#include "memtrace.h"


#include <iostream>

#include "gtest_lite.h"
int main() {

    TEST(XORCodeCONSTR, 011010){
        XORCode a("011010");
        EXPECT_STREQ("011010", a.getCoderDetails().c_str());
    } END

    TEST(Coder*XORCODE, 1000101){
        Coder* a = new XORCode("1000101");
        EXPECT_STREQ("1000101", a->getCoderDetails().c_str());
        delete a;
    } END

    TEST(codelist, 101){
        CodeList a;
        a.add(new XORCode("101"));
        a.add(new XORCode("01"));
        EXPECT_STREQ("101", a[0]->getCoderDetails().c_str());
        EXPECT_STREQ("01", a[1]->getCoderDetails().c_str());
    } END

    TEST(TestRemove, fromCodeList){
        CodeList a;
        a.add(new XORCode("101"));
        a.add(new XORCode("01"));
        a.remove(0);
        EXPECT_STREQ("01", a[0]->getCoderDetails().c_str());
    } END

    TEST(EncodeXOR, 16_key="10101010"){
        XORCode coder("1010101010101010");
        String tocode("10000000010000");
        EXPECT_STREQ("1000101010111010", coder.encode(tocode).c_str());
    } END

    TEST(Encode/DecodeXOR, 3_key="1"){
        XORCode coder("1");
        String tocode("11");
        String codedtext = coder.encode(tocode);
        EXPECT_STREQ("00000010", codedtext.c_str());
        EXPECT_STREQ("00000011", coder.decode(codedtext).c_str());
    } END

    TEST(MorseCodeEncodeDecode, abc){
        MorseCode coder;
        String tocode("abc");
        String encoded(coder.encode(tocode));
        EXPECT_STREQ(".- -... -.-. ", encoded.c_str());
        EXPECT_STREQ("abc", coder.decode(encoded).c_str());
    } END

    TEST(WriteToFile, coders){
        CodeList a;
        FileHandler b;
        b.setOutput("test.txt");
        a.add(new XORCode("101"));
        a.add(new XORCode("01"));
        a.add(new XORCode("01"));
        a.add(create<MorseCode>(26));
        a.add(create<XORCode>("101"));
        a.saveToFile(b);
    } END

    TEST(ReadFromFile, coders){
        FileHandler b;
        b.setInput("test.txt");
        CodeList a;
        b.readFromFile(a);
        String mcoded = a[3]->encode("abc");
        String tocode("11");
        String xcoded = a[1]->encode(tocode);
        EXPECT_STREQ("MorseCode", a[3]->getWhichCoder().c_str());
        EXPECT_STREQ(".- -... -.-. ", mcoded.c_str());
        EXPECT_STREQ("00000010", xcoded.c_str());
    } END

    TEST(ExpectThrows, coders){
        FileHandler b;
        CodeList a;
        EXPECT_THROW(b.readFromFile(a), const char*);
        EXPECT_THROW(a.add(new XORCode("2")), const char*);
        a.add(new XORCode("101"));
        String tocode("20");
        EXPECT_THROW(a[0]->encode(tocode), const char*);
    } END

}
