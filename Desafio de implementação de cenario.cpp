#include <iostream>#include <fstream>#include <string>#include <sstream>#include <vector>#include <algorithm>#include <cctype>using namespace std;struct Product {    string name;    string description;    double price;    int quantity;};void importData(vector<Product>& products, const string& filename) {    ifstream file(filename);    if (!file) {        cout << "Erro ao abrir o arquivo." << endl;        return;    }    products.clear();    string line;    int count = 0;    while (getline(file, line) && count < 100) {        stringstream ss(line);        string name, description, priceStr, quantityStr;        getline(ss, name, ',');        getline(ss, description, ',');        getline(ss, priceStr, ',');        getline(ss, quantityStr, ',');        double price = stod(priceStr);int quantity = stoi(quantityStr);        Product product;product.name = name;        product.description = description;               product.price = price;         product.quantity = quantity;        products.push_back(product);        count++;    }    file.close();    cout << "Dados importados com sucesso." << endl;}// Declaracão da funcão heapifyvoid heapify(vector<Product>& products, int size, int rootIndex);// Funcão de comparacão para ordenacão por nomebool compareByName(const Product& a, const Product& b) {    return a.name < b.name;}// Função para verificar se uma string representa um número válidobool isValidNumber(const string& str) {    bool hasDecimal = false;    for (char c : str) {        if (!isdigit(c)) {            if (c == '.' && !hasDecimal) {                hasDecimal = true;            } else {                return false;            }        }    }    return true;}// Funcão para adicionar um produtovoid addProduct(vector<Product>& products) {    Product product;        cout << "Nome: ";    cin.sync();    getline(cin, product.name);        cout << "Descricao: ";    cin.sync();    getline(cin, product.description);	  cout << "Preco: ";        string priceStr;        cin >> priceStr;			if (!isValidNumber(priceStr)) {    cout << "Entrada invalida para preco. Tente novamente." << endl;    return;}	    	 cout << "Quantidade: ";	string quantityStr;	cin >> quantityStr;				if (!isValidNumber(quantityStr)) {    cout << "Entrada invalida para preco. Tente novamente." << endl;    return;}		product.price = stod(priceStr);	product.quantity = stod(quantityStr);	    products.push_back(product);}// Funcão para remover um produtovoid removeProduct(vector<Product>& products, const string& productName) {    auto it = find_if(products.begin(), products.end(), [&](const Product& p) {        return p.name == productName;    });    if (it != products.end()) {        products.erase(it);        cout << "Produto removido com sucesso." << endl;    } else {        cout << "Produto nao encontrado." << endl;    }}// Funcão para atualizar um produtovoid updateProduct(vector<Product>& products, const string& productName) {	auto it = find_if(products.begin(), products.end(), [&](const Product& p) {        return p.name == productName;    });    if (it != products.end()) {        Product& product = *it;        cout << "Novo nome (atual: " << product.name << "): ";        cin.sync();        getline(cin, product.name);        cout << "Nova descricao (atual: " << product.description << "): ";        cin.sync();        getline(cin, product.description);       cout << "Novo preco (atual: " << product.price << "): ";        string priceStr;        cin >> priceStr;;        if (!isValidNumber(priceStr)) {            cout << "Entrada invalida para preco. Tente novamente." << endl;            return;        }        product.price = stod(priceStr);        cout << "Nova quantidade (atual: " << product.quantity << "): ";        string quantityStr;        cin >> quantityStr;        if (!isValidNumber(quantityStr)) {            cout << "Entrada invalida para quantidade. Tente novamente." << endl;            return;        }        product.quantity = stod(quantityStr);        cout << "Produto atualizado com sucesso." << endl;    } else {        cout << "Produto nao encontrado." << endl;    }}// Funcão para buscar um produto por nome usando busca bináriavoid searchProduct(const vector<Product>& products, const string& productName) {    auto it = lower_bound(products.begin(), products.end(), productName, [](const Product& p, const string& name) {    	        return p.name < name;    });    if (it != products.end() && it->name == productName) {        const Product& product = *it;        cout << "Produto encontrado: " << endl;        cout << "Nome: " << product.name << endl;        cout << "Descricao: " << product.description << endl;        cout << "Preco: " << product.price << endl;        cout << "Quantidade: " << product.quantity << endl;    } else {        cout << "Produto nao encontrado." << endl;    }}// Funcão para exibir todos os produtos em ordem crescente ou decrescente de precovoid displayProductsByPrice(const vector<Product>& products, bool ascendingOrder) {    vector<Product> sortedProducts = products;    // Aplicar Heapsort para classificar os produtos por preco    int size = sortedProducts.size();    for (int i = size / 2 - 1; i >= 0; i--) {        heapify(sortedProducts, size, i);    }    for (int i = size - 1; i >= 0; i--) {        swap(sortedProducts[0], sortedProducts[i]);                heapify(sortedProducts, i, 0);    }    if (!ascendingOrder) {        reverse(sortedProducts.begin(), sortedProducts.end());    }    cout << "Produtos ordenados por preco:" << endl;    for (const Product& product : sortedProducts) {        cout << "Nome: " << product.name << ", Preco: " << product.price << endl;    }}void heapify(vector<Product>& products, int size, int rootIndex) {    int largest = rootIndex;    int leftChild = 2 * rootIndex + 1;        int rightChild = 2 * rootIndex + 2;    if (leftChild < size && products[leftChild].price > products[largest].price)        largest = leftChild;            if (rightChild < size && products[rightChild].price > products[largest].price)        largest = rightChild;    if (largest != rootIndex) {        swap(products[rootIndex], products[largest]);        heapify(products, size, largest);    }}// Funcão para exibir todos os produtos em ordem alfabética crescente ou decrescente por nomevoid displayProductsByName(const vector<Product>& products, bool ascendingOrder) {    vector<Product> sortedProducts = products;        sort(sortedProducts.begin(), sortedProducts.end(), compareByName);    if (!ascendingOrder) {        reverse(sortedProducts.begin(), sortedProducts.end());    }    cout << "Produtos ordenados por nome:" << endl;        for (const Product& product : sortedProducts) {        cout << "Nome: " << product.name << ", Preco: " << product.price << endl;    }}int main() {    vector<Product> products;    importData(products, "produtos.txt");    int choice;        string productName;    do {        system("cls");        cout << "==== Menu ====" << endl;        cout << "1. Adicionar produto" << endl;        cout << "2. Remover produto" << endl;        cout << "3. Atualizar produto" << endl;        cout << "4. Buscar produto por nome" << endl;        cout << "5. Exibir produtos por preco (crescente)" << endl;        cout << "6. Exibir produtos por preco (decrescente)" << endl;        cout << "7. Exibir produtos por nome (crescente)" << endl;        cout << "8. Exibir produtos por nome (decrescente)" << endl;        cout << "0. Sair" << endl;        cout << "Escolha uma opcao: ";        cin >> choice;        switch (choice) {            case 1:                addProduct(products);                system("pause");                break;                            case 2:                cout << "Digite o nome do produto a ser removido: ";                cin.sync();                getline(cin, productName);                                removeProduct(products, productName);                system("pause");                break;            case 3:                cout << "Digite o nome do produto a ser atualizado: ";                cin.sync();                getline(cin, productName);                                updateProduct(products, productName);                system("pause");                break;            case 4:                cout << "Digite o nome do produto a ser buscado: ";                cin.sync();                getline(cin, productName);                searchProduct(products, productName);                system("pause");                break;            case 5:                displayProductsByPrice(products, true);                system("pause");                break;            case 6:                displayProductsByPrice(products, false);                system("pause");                break;            case 7:                displayProductsByName(products, true);                system("pause");                break;            case 8:                displayProductsByName(products, false);                system("pause");                break;            case 0:                cout << "Encerrando o programa..." << endl;                system("pause");                break;            default:                cout << "Opcao invalida. Tente novamente." << endl;                system("pause");                break;        }                cout << endl;    } while (choice != 0);    return 0;}