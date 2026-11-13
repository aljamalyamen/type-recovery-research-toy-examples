#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector> //for vectors alphabet, eliasgammapositions, & positions
#include <string> //string methods to read data correctly
#include <fstream> //file methods, open and close, and read encoded file
#include <iostream> //for output and input *I/O*
#include <sstream> //stringstream method to cut the lines to recieve correct data similar to .split() in python

using namespace std; 

struct symbol
{
    char data;
    int frequency;
    vector<string> elias_gamma_positions;
    vector<int> positions;
    unsigned int n_bits_elias_gamma;
};

unsigned int elias_gamma_to_int(const string& code) {
    unsigned int zeros = 0;
    
    //counts the amount of zeros leading zeros for the next method, in order to convert the second section of the binary (after the firs one) into an int, as 1 is the limiter
    while (zeros < code.size() && code[zeros] == '0') 
    {
        zeros++;
    }
    
    //Converts the binary string into an int value that is the decoded position of the symbol
    unsigned int result = 0;
    for (unsigned int i = zeros; i < 2 * zeros + 1 && i < code.size(); i++) {
        result = result * 2 + (code[i] - '0');
    }
    
    return result;
}

bool read_input_from_file(string filename , vector<symbol>& alphabet)
{
    ifstream gamma_txt(filename); 
    //open file

    string line;
    //create a variable to store data read from each line int the file


    if (gamma_txt.is_open())    
    //checks if file opened correctly, if true, continue

    {
        /*reading each line of text from the file until the end of file, 
        hence the use of a while loop*/
        while (getline(gamma_txt , line))
        {
            stringstream individual_line(line); 
            //used to parse the string into individual blocks, sort of like the .split method in python

            symbol character; 
            //initializing a variable "character" with datatype symbol to overload each part of the struct
            
            string fline; 
            //initialized a string to save every string extracted from the while loop in order to correctly overload the struct
            getline(individual_line,fline,' ');
            //used to get the first character, will keep reading line until the program encounters a blankspace delimiter
            character.data=line.at(0); 
           // character.data=individual_line.get();
            //
            //assigns character.data the symbol using the first character found hence the .at method as this is a string
            character.n_bits_elias_gamma = 0;

           // while (getline(individual_line,fline,' '))
            while (individual_line >> fline)
            //this loop uses the rest of the data after the symbol, in this case its the strings that make up the binary elias gamma encoding
            {
              //  if (fline.empty()) continue;
                character.elias_gamma_positions.push_back(fline);
                //pushes each substring of data into the elias_gamma_positions vector then jumps to the next substring until getline encounters endl
                
                character.n_bits_elias_gamma+=fline.size();

            }
            character.frequency=character.elias_gamma_positions.size();
            //takes the size of the elias_gamma_positions and sets it to struct frequency

            for (int i = 0 ; i < (int)character.elias_gamma_positions.size() ; i++) 
            {
                string gamma = character.elias_gamma_positions.at(i);
                int decoded = elias_gamma_to_int(gamma)-1;
                character.positions.push_back(decoded);
            }



            alphabet.push_back(character); 
            //pushes the entire struct into vector alphabet (vector alphabet was passed by reference because a: complex data type and b: we need to alter it but not return)
        }

        return true;
        //at the end of all of these methods return true to show the file successfully opened and read
    }
    else
    {
        return false;
    }

}

void decode_positions_and_populate_original_message(const symbol& letter ,  string& message)
{
    for (unsigned int i = 0; i < letter.positions.size(); i++) 
    //loops for the size of how many positions the symbol uses in the struct
    {
        unsigned int position = letter.positions[i];
        if (position < message.size()) 
        //checks to see if the position of the letter to be inserted into the message is less than the size to avoid loss
        {
            message[position] = letter.data;
            //inserts the corresponding symbol of the struct inside of the decoded message string according to its correct index
        }
    }
}

unsigned int original_message_size(const vector<symbol>& alphabet)

{
    unsigned int size=0;
    for (const symbol& s : alphabet) 
    {
        size+=s.frequency;
    }
    return size;
}





void print_results(const vector<symbol>& alphabet , const string message)
{
    cout<<"Alphabet:"<<endl;
    for (symbol s : alphabet)
    {
        cout<<"Symbol: "<<s.data<<", Frequency: "<<s.frequency<<" "<<endl;
        //prints each individual structure and its corresponding value
        cout<<"Positions: ";
        for (int i = 0 ; i < s.positions.size() ; i++)
        {
            cout<<s.positions.at(i)<<" ";
        }
        //after elias_gamma_to_int function, the positions vector was populated with the correct positions
        cout<<endl;

        cout<<"Number of bits to represent the positions: "<<s.n_bits_elias_gamma<<endl;
        //this line prints the number of bits for the specific sructure in this loop
    }
    cout<< "Decoded message: "<< message <<endl;
}






#endif
