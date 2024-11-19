#include"csv.hpp"
void CSV::split(string& str, vector<string>& out){
    stringstream ss(str);
    string frase;
    while(getline(ss, frase, ';'))
        out.push_back(frase); 
}

string CSV::getHeader(IReadable& object){
    vector<string>out;
    object.GetCampos(out);
    return out[0] +";"+ out[1] +";"+ out[2];
}

void CSV::readLine(string& head, string& line, IReadable& object){
    vector<string>header;
    vector<string>attribute;
    
    split(head, header);
    split(line, attribute);

    for(unsigned long k=0; k<3; k++){
        object.setAtributo(header[k],attribute[k]);
    }
}

string CSV::write(IReadable& object){
    return object.GetAtributo("nome") +";"+ object.GetAtributo("idade") +";"+ object.GetAtributo("cpf");
}