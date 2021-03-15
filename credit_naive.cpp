// Naive implementation of C++ program to pay up to 20 credit cards down to same utilization percentage, or as close as possible, given the respective card limits and the amount the user is able to pay at this time

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main() {

// declare variables
    
    class Card {
        public:
            string nickname;
            double limit;
            double old_balance;
            double new_balance;
            double payment;
            double old_utilization;
            double new_utilization;
            bool payIt;
            double nb_percent;
    };

    Card cards[4]; // array of class card, custom to my current cards
    double L; // total of all Limits
    double B; // Initial total of all Balances
    double b1, b2, b3, b4 = 0; // respective balances for each card
    double P; // total Payment making today
    double p1, p2, p3, p4 = 0; // respective payment amounts to apply to cards
    double NTB; // New Total of Balances after payment distributed to all balances
    double NPB; // New 'Print' Balance, add back in for printing 'New balances total: '
    double Ubefore; // total all cards Utilization before P applied to B -- currently unused
    double Uafter; // total all cards Utilization after P applied to B
    double NTL = 0; // New Total of all Limits for cards with utilization above Uafter
    
// hard code my card info since this 'my' program is just for me:
    
    cards[0].nickname = "Discover";
    cards[1].nickname = "Chase";
    cards[2].nickname = "AmEx";
    cards[3].nickname = "CapOne";
    
// read in current balances for each card
    
    cout << endl;
    for (int i=0; i<4; i++) {
        cout << "Enter " + cards[i].nickname + " limit: ";
        cin >> cards[i].limit;
        cout << "Enter " + cards[i].nickname + " balance: ";
        cin >> cards[i].old_balance;
        cout << endl;
    }

// find L, the total of all limits

    for (int i=0; i<4; i++) {
        L += cards[i].limit;
    }
    
// calculate B, the total current balance
    
    b1 = (cards[0].old_balance);
    b2 = (cards[1].old_balance);
    b3 = (cards[2].old_balance);
    b4 = (cards[3].old_balance);
    B = b1 + b2 + b3 + b4;
    
// find Ubefore, the total initial utilization on all cards
    
    Ubefore = B/L;
    
// read in P, the amount of today's payment

    cout << "Amount you can pay on your cards today: ";
    cin >> P;
    cout << endl;
    
// calculate NTB, the New Balance total after payment P is applied
    
    NTB = B - P;
    
// find Uafter, the total utilization on all cards after total payments P is applied to total balances B
    
    Uafter = NTB/L;
    
// find utilization for each card
    
    for (int i=0; i<4; i++) {
        cards[i].old_utilization = cards[i].old_balance/cards[i].limit;
    }
    
// figure out which cards will be paid today and set 'payIt' member variable
    
    for (int i=0; i<4; i++) {
        if (cards[i].old_utilization > Uafter) cards[i].payIt = true;
        else cards[i].payIt = false;
    }
    
// find New Total Limit (NTL) for cards with payIt = true
    
    for (int i=0; i<4; i++) {
        if (cards[i].payIt) NTL += cards[i].limit;
        else {
            NTB -= cards[i].old_balance; // need to adjust NB so nb_percentages are correct
            NPB += cards[i].old_balance;
        }
    }
    
// for each card calculate nb_percent, the percent of the new balance that a card will be after payment applied
    
    for (int i=0; i<4; i++) {
        if (cards[i].payIt) cards[i].nb_percent = cards[i].limit/NTL;
        else cards[i].nb_percent = 0;
    }
    
// calculate payment for each card: previous balance - (that card's percentage of new total of balances * new total of balances)
// need to get rid of the p1...p4 and b1...b4 check so can do for loop
    
    if (cards[0].payIt) cards[0].payment = p1 = b1 - (cards[0].nb_percent*NTB);
    else cards[0].payment = 0;
    
    if (cards[1].payIt) cards[1].payment = p2 = b2 - (cards[1].nb_percent*NTB);
    else cards[1].payment = 0;
    
    if (cards[2].payIt) cards[2].payment = p3 = b3 - (cards[2].nb_percent*NTB);
    else cards[2].payment = 0;
    
    if (cards[3].payIt) cards[3].payment = p4 = b4 - (cards[3].nb_percent*NTB);
    else cards[3].payment = 0;
    
// calculate new balances and utilizations
    
    for (int i=0; i<4; i++) {
        cards[i].new_balance = cards[i].old_balance - cards[i].payment;
        cards[i].new_utilization = cards[i].new_balance/cards[i].limit;
    }
    
// check correctness of calculations and print output
    
    if (1) {//(p1+p2+p3+p4 == P) { // if balances entered correctly
        
    // ff. 2 lines add commas to dollar amts:
        
        locale loc("");
        cout.imbue(loc);

    // print all information
        
        cout << "- Old balances total: $" << B << endl;
        cout << "- Old utilization total: %" << Ubefore*100 << endl << endl;
        for (int i=0; i<4; i++) {
            double temp_pmt = cards[i].payment;
            double temp_lim = cards[i].limit;
            double temp_ob = cards[i].old_balance;
            double temp_nb = cards[i].new_balance;
            double temp_ou = cards[i].old_utilization;
            double temp_nu = cards[i].new_utilization;
            cout << i+1 << ") Name:    " << cards[i].nickname << endl <<
                    "   Payment: $" << fixed << setprecision(2) << temp_pmt << endl << endl <<
                    "   Limit:           $" << fixed << setprecision(2) << temp_lim << endl <<
                    "   Old Balance:     $" << fixed << setprecision(2) << temp_ob << endl <<
                    "   New Balance:     $" << fixed << setprecision(2) << temp_nb << endl <<
                    "   Old Utilization: %" << fixed << setprecision(2) << temp_ou*100 << endl <<
                    "   New Utilization: %" << fixed << setprecision(2) << temp_nu*100 << endl << endl;
        }
        cout << "- New balances total: $" << NTB + NPB << endl;
        cout << "- New utilization total: %" << Uafter*100 << endl << endl;
    }
    else { // if balances not entered correctly
        cout << "bad entries, please restart program" << endl;
        cout << "(p1+p2+p3+p4 == P): " << p1 << "+" << p2  << "+" << p3  << "+" << p4 << "==" << P << endl;
    }
}
