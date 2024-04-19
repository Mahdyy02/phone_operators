#include <bits/stdc++.h>

#define ui unsigned int

class subscriber{
    protected:
        ui phone_number;
        std::string name;
        std::string subscription_date;
        ui minute_price;
        std::map<ui, ui> call_register;
    public:
        virtual void call() = 0;
        virtual float compute_bonus() = 0;
        void save_call(ui called_number, ui call_duration){
            this->call_register[called_number]+=call_duration;
        }

        subscriber(ui phone_number, std::string name, std::string subscription_date, ui minute_price){
            this->phone_number = phone_number;
            this->name = name;
            this->subscription_date = subscription_date;
            this->minute_price = minute_price;
        }
};

class prepaid_subscriber: private subscriber{
    private:
        float prepaid_sum;
    public:
        void recharge_balance(float paid_amount){
            this->prepaid_sum+=paid_amount;
        }
        void call(ui call_duration){
            this->prepaid_sum-= (float)call_duration*this->minute_price;
        }

        prepaid_subscriber(ui phone_number, std::string name, std::string subscription_date, ui minute_price, int prepaid_sum): subscriber(phone_number, name, subscription_date, minute_price){
            this->prepaid_sum = prepaid_sum;
        }

        float compute_bonus(){
            return prepaid_sum*0.1;
        }
};

class postpaid_subscriber: private subscriber{
    private:
        ui consumption;
        ui *free_phone_numbers = new ui[5];
    public:
        void call(ui phone_number, ui call_duration){

            bool exist = false;
            for(int i = 0; i < 5; ++i){
                if(phone_number == this->free_phone_numbers[i]){
                    exist = true;
                    break;
                }
            }

            this->consumption+= (float)call_duration*this->minute_price*(!exist);
        }
        int operator[](int index){
            if(index >= 0 && index < 5)
                return this->free_phone_numbers[index];
            else
                return -1;
        }
        postpaid_subscriber(ui phone_number, std::string name, std::string subscription_date, ui minute_price, ui consumption, ui* free_phone_numbers): subscriber(phone_number, name, subscription_date, minute_price){
            this->consumption = consumption;
            for(int i = 0; i < 5; ++i){
                this->free_phone_numbers[i] = free_phone_numbers[i];
            }
        }

        float compute_bonus(){
            return consumption*0.15;
        }
};

class subscriber_list {
private:
    std::vector<subscriber*> subscribers; 

public:
    void add_subscriber(subscriber* new_subscriber) {
        subscribers.push_back(new_subscriber);
    }

    void delete_subscriber(subscriber* subscriber_to_delete) {
        auto it = std::find(subscribers.begin(), subscribers.end(), subscriber_to_delete);
        if (it != subscribers.end()) {
            subscribers.erase(it);
            delete subscriber_to_delete; 
        }
    }

    void print_bonuses() {
        for (subscriber* sub : subscribers) {
            std::cout <<"Bonus: $" << sub->compute_bonus() << std::endl;
        }
    }

    ~subscriber_list() {
        for (subscriber* sub : subscribers) {
            delete sub;
        }
    }
};


int main(){

    return 0;
}