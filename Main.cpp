#include<iostream>
#include<fstream>
#include <iomanip>

#pragma pack(push,1)
struct Header
{
    uint32_t prefix;
    uint8_t major_version;
    uint8_t minor_version;
    uint8_t exchange;
    uint64_t sequence_no;
    uint8_t message_count;
    uint8_t message_size;
    
    friend std::ostream& operator<< (std::ostream&, const Header& h);
};

struct Book{
uint8_t type;
uint8_t msg_size;
uint16_t product;
uint8_t has_bid;
uint8_t has_ask;
friend std::ostream& operator<< (std::ostream&, const Book& b);
};

struct LevelData{
uint64_t price;
uint64_t size;
friend std::ostream& operator<< (std::ostream&, const LevelData& l);
};

struct Trade {
uint8_t type;
uint8_t msg_size;
uint16_t product;
uint64_t price;
uint64_t size;
friend std::ostream& operator<< (std::ostream&, const Trade& t);
};
#pragma pack(pop)

 enum message_types {
     Book_Type=1,
     Trade_Type=2
 };

void check_File_Failure(std::ifstream& in_data, const std::string& msg){
if(in_data.fail()) {
      std::cout << msg << std::endl;
      exit(1);
   }
   
}

std::ostream& operator<< (std::ostream&, const Header& header){
std::cout << std::setw(30) << "Header!!" <<std::endl;
std::cout  << "prefix"<< " : " <<std::dec<< header.prefix<<std::endl;
std::cout  <<"sequence_no" << " : " <<+header.sequence_no<<std::endl;
std::cout << "exchange : " <<+header.exchange<<std::endl;
std::cout << "major_version : " <<+header.major_version<<std::endl;
std::cout << "minor_version : " <<+header.minor_version<<std::endl;
std::cout << "message_count : " << +header.message_count<<std::endl;
std::cout << "message_size : " << +header.message_size<<std::endl;
 }

std::ostream& operator<< (std::ostream&, const Book& book){
std::cout << "Message type is : Book" <<std::endl;
std::cout << "type : "  << +book.type<<std::endl;
std::cout << "has_ask : " << +book.has_ask <<std::endl;
std::cout << "has_bid : " << +book.has_bid<<std::endl;
std::cout << "msg_size : " << +book.msg_size<<std::endl;
std::cout << "product : " << +book.product<<std::endl;
 }

std::ostream& operator<< (std::ostream&, const Trade& trade){
std::cout << "Message type is: Trade" <<std::endl;
std::cout << "type : " <<+trade.msg_size<<std::endl;
std::cout << "has_ask : " <<+trade.price<<std::endl;
std::cout << "has_bid : " <<+trade.product<<std::endl;
std::cout << "msg_size : " <<+trade.size<<std::endl;
std::cout << "product : " <<+trade.type<<std::endl;
 }

std::ostream& operator<< (std::ostream&, const LevelData& level_data){
std::cout << " level data !!" <<std::endl;
std::cout << "type : " <<+level_data.price<<std::endl;
std::cout << "has_ask" <<+level_data.size<<std::endl;
 }


int main()
{
Header header;

std::string file_name = "datadump.bin";
std::ifstream in_data(file_name, std::ios::out|std::ios::binary);

check_File_Failure(in_data,"Error occurred at reading time!");

in_data.read((char*) &header,sizeof(Header));
check_File_Failure(in_data, "Error occurred at reading time!");
std::cout<<header;

int temp_message_count = header.message_count;

while(temp_message_count){
uint8_t type = in_data.peek();

if(type == Book_Type){
 Book book;
LevelData level_data;
in_data.read((char*) &book,sizeof(Book));
check_File_Failure(in_data, "Error reading book");

std::cout<<book<<std::endl;

in_data.read((char*) &level_data,sizeof(LevelData));
check_File_Failure(in_data, "Error reading level data");
std::cout<<level_data<<std::endl;
}

else if (type == Trade_Type){
Trade trade;
in_data.read((char*) &trade,sizeof(Trade));
check_File_Failure(in_data, "Error reading trade");
std::cout<<trade<<std::endl;
}

    temp_message_count--;
}

 in_data.close();
}


















