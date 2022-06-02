#include "coder.h"
#include "codelist.h"
#include "string5.h"
#include "filehandler.h"
#include "xorcode.h"
#include "morsecode.h"

#include "memtrace.h"


#include <iostream>

#ifdef CPORTA
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
#else
int main(){
    int a = 0;
    FileHandler fh;
    CodeList cl;
    std::cout << "Coder program menu" << '\n' << "-----------------------\n";
    while(a < 1 || a > 9) {
        std::cout << "Choose a menu option:\n"
                  << "1. Set input file\n2. Set output file\n3. Add coder\n4. Select coder to encode with\n5. Select coder to decode with\n6. Save coders to file\n7. Read coders from file\n8. Remove coder from codelist\n9. Exit program"
                  << std::endl;
        std::cin >> a;
        if (a == 1) {
            String ifn("");
            std::cout << "Give an input file name: (input file must exist)" << std::endl;
            std::cin >> ifn;
            fh.setInput(ifn);
            a = 0;
        } else if (a == 2) {
            String ofn("");
            std::cout << "Give an output file name: (if the file doesn't exist it will generate it)" << std::endl;
            std::cin >> ofn;
            fh.setOutput(ofn);
            a = 0;
        } else if (a == 3) {
            int b = 0;
            while (b < 1 || b > 3) {
                std::cout << "What type of coder do you want to create?\n"
                          << "1. XORCoder\n2. MorseCoder\n3. Exit to main menu" << std::endl;
                std::cin >> b;
            }
            if (b == 1) {
                try{
                    String key("");
                    std::cout << "What key do you want to code with? (Binary only, e.g. 01110)" << std::endl;
                    std::cin >> key;
                    cl.add(new XORCode(key));
                    std::cout << "XORCoder added" << std::endl;
                    a = 0;
                }catch(const char* err){
                    std::cout << err;
                    a = 0;
                }
            } else if (b == 2) {
                cl.add(new MorseCode());
                std::cout << "MorseCoder added" << std::endl;
                a = 0;
            } else if (b == 3) {
                a = 0;
            }
        } else if (a == 4) {
            int b = -1;
            std::cout << "Available coders:\n";
            for (int i = 0; i < cl.getSize(); ++i) {
                std::cout << i << ". " << cl[i]->getWhichCoder();
                std::cout << " " << cl[i]->getCoderDetails().c_str() << '\n';
            }

            while (b < 0 || b > cl.getSize() - 1) {
                std::cout << "Select a coder from the list above or exit with -1." << std::endl;
                std::cin >> b;
                if (b == -1) {
                    a = 0;
                    break;
                }
            }
            try{
                if (b != -1) {
                    String coder("XORCode");
                    String msgtocode("");
                    if (cl[b]->getWhichCoder() == coder) {
                        std::cout << "Write a binary message you want to encode with XORCode: " << std::endl;
                        std::cin >> msgtocode;
                        std::cout << "The coded message is: " << cl[b]->encode(msgtocode).c_str() << std::endl;
                        a = 0;
                    } else {
                        std::cout << "Write a message you want to encode with MorseCode: " << std::endl;
                        std::cin >> msgtocode;
                        std::cout << "The coded message is: " << cl[b]->encode(msgtocode).c_str() << std::endl;
                        a = 0;
                    }
                }
            }catch(const char* err){
                std::cout << err;
                a = 0;
            }
        } else if (a == 5) {
            int b = -1;
            std::cout << "Available coders:\n";
            for (int i = 0; i < cl.getSize(); ++i) {
                std::cout << i << ". " << cl[i]->getWhichCoder();
                std::cout << " " << cl[i]->getCoderDetails().c_str() << '\n';
            }

            while (b < 0 || b > cl.getSize() - 1) {
                std::cout << "Select a coder from the list above or exit with -1." << std::endl;
                std::cin >> b;
                if (b == -1) {
                    a = 0;
                    break;
                }
            }
            try{
                if (b != -1) {
                    String coder("XORCode");
                    String msgtocode;
                    if (cl[b]->getWhichCoder() == coder) {
                        std::cout << "Write a binary message you want to decode with XORCode: " << std::endl;
                        std::cin >> msgtocode;
                        std::cout << "The decoded message is: " << cl[b]->decode(msgtocode).c_str() << std::endl;
                        a = 0;
                    } else {
                        std::cout << "Write a message you want to decode with MorseCode: " << std::endl;
                        std::cin >> msgtocode;
                        std::cout << "The decoded message is: " << cl[b]->decode(msgtocode).c_str() << std::endl;
                        a = 0;
                    }
                }
            }catch(const char* err){
                std::cout << err;
                a = 0;
            }
        }else if(a == 6){
            try{
                cl.saveToFile(fh);
                std::cout << "Coders saved successfully to: " << fh.getOutput().c_str() << std::endl;
            }catch(const char* err){
                std::cout << err;
                a = 0;
            }

            a = 0;
        }else if(a == 7){
            try{
                fh.readFromFile(cl);
                std::cout << "Successfully read " << cl.getSize() << " coders from " << fh.getInput().c_str() << std::endl;
            }catch(const char* err){
                std::cout << err;
                a = 0;
            }

            a = 0;
        }else if(a == 8){
            int c = -1;
            std::cout << "Available coders:\n";
            for (int i = 0; i < cl.getSize(); ++i) {
                std::cout << i << ". " << cl[i]->getWhichCoder();
                std::cout << " " << cl[i]->getCoderDetails().c_str() << '\n';
            }

            while (c < 0 || c > cl.getSize() - 1) {
                std::cout << "Select a coder from the list above or exit with -1." << std::endl;
                std::cin >> c;
                if (c == -1) {
                    a = 0;
                    break;
                }
            }
            try{
                if (c != -1) {
                    cl.remove(c);
                    a = 0;
                }
            }catch(const char* err){
                std::cout << err;
                a = 0;
            }
        }else if(a == 9){
            break;
        }
    }
}
#endif
