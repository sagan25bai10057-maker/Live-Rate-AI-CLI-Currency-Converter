#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;
bool isValidCurrencyCode(const string& code) {
    if(code.length()!=3)
        return false;
    for(char c:code){
        if(!isalnum(c))
            return false;
    }
    return true;
}
string read_file_content(const string& filename){
    ifstream file(filename);
    if (!file.is_open()) return "";
    string content((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    file.close();
    return content;
}
void generate_ai_summary(string base_currency,string target_currency,double live_rate,double amount) {
    double total=amount*live_rate;
    cout<<"\n=========================================\n";
    cout<<"🤖 GENERATING AI FINANCIAL SUMMARY...\n";
    cout<<"=========================================\n";
    cout<<"\"Market Insight Report: Analysis of " << base_currency << " to " << target_currency << ".\n\n";
    cout<<"Based on real-time API telemetry, 1 " << base_currency << " is currently trading at " << live_rate << " " << target_currency << ".\n";
    cout<<"Your transaction of " << amount << " " << base_currency << " yields an output of " << total << " " << target_currency << ".\n\n";
    cout<<"[Volatility Risk Evaluation]:\n";
    if(live_rate>1.0){
        cout<<"-> The "<<base_currency<<" maintains historical strength over the "<<target_currency<<".\n";
        cout<<"-> Macroeconomic AI Indicator: Low short-term buying risk. Optimal execution window.\n";
    }
    else{
        cout<<"-> The "<<target_currency<<" is showing strong resistance against the "<<base_currency<<".\n";
        cout<<"-> Macroeconomic AI Indicator: High conversion cost. Consider holding if immediate liquidation isn't required.\"\n";
    }
    cout<<"=========================================\n";
}
int main(){
    string api_key;
    char choice;
    cout<<"--- Live AI Currency Interface ---\n\n";
    cout<<"Enter your ExchangeRate-API Key: ";
    cin>>api_key;
    if(api_key.find_first_of(";&|`$<>")!=string::npos){
        cout<<"\n ERROR: Malicious characters detected in API Key!\n";
        return 1;
    }
    do{
        string base_curr,target_curr;
        double amount;
        cout<<"\n-------------------------------------------\n";
        cout<<"Enter Base Currency (e.g., USD, EUR, INR): ";
        cin>>base_curr;
        cout<<"Enter Target Currency (e.g., EUR, INR, GBP, PKR): ";
        cin>>target_curr;
        cout<<"Enter Amount to Convert: ";
        cin>>amount;
        if(!isValidCurrencyCode(base_curr) || !isValidCurrencyCode(target_curr)){
            cout<<"\n ERROR: Invalid Currency Code Format!\n";
            cout<<"Financial APIs require official 3-letter ISO codes (e.g., USD, INR, EUR).\n";
            cout<<"\nWould you like to try again? (Y/N): ";
            cin>>choice;
            continue;
        }
        string url="https://v6.exchangerate-api.com/v6/"+api_key+"/pair/"+base_curr+"/"+target_curr;
        string output_file="rate_data.txt";
        string command="powershell -Command \"(Invoke-WebRequest -UseBasicParsing -Uri '"+url+"').Content\" > "+output_file;
        cout<<"\nFetching real-time exchange streams...\n";
        system(command.c_str());
        string raw_json=read_file_content(output_file);
        if(raw_json.find("unsupported-code")!=string::npos){
            cout<<"\n ERROR: Invalid Currency Code Entered!\n";
            cout<<"-------------------------------------------\n";
            cout<<"Financial APIs require official 3-letter ISO codes.\n";
            cout<<"Common valid inputs include: USD, EUR, GBP, JPY, INR, PKR, AED.\n";
            cout<<"\nWould you like to try again? (Y/N): ";
            cin>>choice;
            continue;
        }
        if(raw_json.empty() || raw_json.find("conversion_rate")==string::npos){
            cout<<"\n ERROR: Unable to pull market data.\n";
            cout<<"Please verify that your API Key is correct and your internet connection is active.\n";
            cout<<"\nWould you like to try again? (Y/N): ";
            cin>>choice;
            continue;
        }
        string look_for="\"conversion_rate\":";
        size_t index=raw_json.find(look_for);
        size_t start_pos=index+look_for.length();
        size_t end_pos=raw_json.find(",",start_pos);
        if(end_pos==string::npos) {
            end_pos=raw_json.find("}",start_pos);
        }
        if(end_pos==string::npos) {
            cout<<"\n ERROR: Parsing failed due to unexpected API response format.\n";
            cout<<"\nWould you like to try again? (Y/N): ";
            cin>>choice;
            continue;
        }
        string rate_string=raw_json.substr(start_pos,end_pos-start_pos);
        try {
            double live_exchange_rate=stod(rate_string);
            cout<<"\n[LIVE DATA SUCCESS]";
            cout<<"\nLive Conversion Rate: 1 "<<base_curr<<" = "<<live_exchange_rate<<" " <<target_curr<<"\n";
            cout<<"Standard Conversion Value: "<<(amount*live_exchange_rate)<<" "<<target_curr<<"\n";
            generate_ai_summary(base_curr,target_curr,live_exchange_rate,amount);
        } catch(const exception& e){
            cout<<"\n ERROR: Numerical conversion failed.\n";
        }
        cout<<"\nWould you like to perform another conversion? (Y/N): ";
        cin>>choice;
    } while(choice=='Y' || choice=='y');
    cout<<"\nThank you for using Live AI Currency Interface. Goodbye!\n";
    return 0;
}