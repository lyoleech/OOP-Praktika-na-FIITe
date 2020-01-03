#include <iostream>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <list>
#include <map>
#include <functional>
#include <fstream>
#include <random>
#include <cmath>
#include <limits>
#include <iomanip>
#include <stack>
#include <queue>
#include <set>
#include <valarray>
#include <forward_list>
#include <iterator>
#include <memory>


//to print vector
////=====================================================================================================
void Print(const int& x)
{
    std::cout<<x<<' ';
}
////=====================================================================================================

////определение функции с переменным числом аргументов
////=====================================================================================================
template <typename Type>
Type Sum(Type first)
{
    return first;
}

template <typename Type, typename... TArgs>
Type Sum(Type first, TArgs... args)
{
    return first + Sum(args...);
};
////=====================================================================================================
//

int main()
{

    //unique and shared
    std::shared_ptr<double> doublePtr;
    double *nakedDoublePtr = new double;
    //doublePtr = nakedDoublePtr; //неявное преобразование //недопустимо
    //nakedDoublePtr = doublePtr; //недопустимо
    doublePtr = std::shared_ptr<double>(nakedDoublePtr);

    //unique владеет ресурсом сам
    //shared делит его с другими указателями
    std::unique_ptr<int> intPtr(new int(2));
    std::unique_ptr<int> intPtr2(new int(2));
    //intPtr = intPtr2;//error
    intPtr = std::move(intPtr2);
    std::unique_ptr< double[]>pda(new double(5));


//работа с классом string
//=====================================================================================================
    std::string input = "Ola!";
    std::wstring unicodeString = L"Ola!";
//=====================================================================================================

//использование функции с переменным числом аргументов
//=====================================================================================================
    std::cout << "There are sums" << std::endl;
    std::cout << Sum(1,2,3) << std::endl;
    std::cout << Sum(1, 2, 3, 4, 5, 10, 100, 1000, 10000, 1, 1, 1) << std::endl;
    std::cout << Sum(1, 2, 3, 4, 5, 10, 100, 1000, 10000, 1, 1, 1, 1, 2, 3, 4, 5, 10, 100, 1000, 10000, 1, 1, 1) << std::endl;
//=====================================================================================================



//работа со стандартными устройствами ввода/вывода
//=====================================================================================================
//базовые типы для работы с потоками лежат в iostream
//для работы с файловыми потоками - лежат в fstream
//для работы с потоками, состоящими из символов - лежат в sstream
//тип istream - input stream - работа с операциями ввода
//тип ostream - output stream - работа с операциями вывода
//экземпляр класса istream cin работает со стандратным устройством ввода
//экземпляр класса ostream cout работает со стандратным устройством вывода
//экземпляр класса ostream cerr связан со стандратным устройством вывода ошибок
//оператор >> перегружен при работе с классом типа istream на ввод информации
    std::cin >> input;
//оператор << перегружен при работе с классом типа ostream на вывод информации
    std::cout<<input<<std::endl;
    std::wcout<<unicodeString<<std::endl;

//потоки нельзя копировать
    std::ofstream output1;
    //std::ofstream output2(output1); //error
    std::ofstream output2;
    //output1 = output2; //error

//Работа с потоком ввода
//В типах istream и ostream существуют переменные, отвечающие за состояние потока
//после операции ввода/вывода. В случае ошибки эти переменные меняют свое значение.
//в консоль выведется значение переменной, сигнализирующее о произошедшей ошибке.
    std::cout << static_cast<bool>(std::cin) << std::endl;
    //std::cin.badbit - неустранимая проблема
    //std::cin.failbit - устранимая проблема, например, чтение char вместо int
//пример использования :
    //std::cin.eofbit - достигнут конец потока
    //Если установлен любой из этих флагов, значение std::cin равно false
    //std::fail(), std::bad(), std::eof() - установлены ли соотвествующие флаги в cin
    //std::good() - все ли нормально?
    int inputInt;
    std::cin >> inputInt; // если подадим строку, произойдет ошибка
    if(!std::cin) {std::cout<<"Was an error!" <<std::endl;}//do sth

    //работа с потоком, пришедшим извне
    auto oldState = std::cin.rdstate(); //получаем текущее состояние потока
    std::cin.clear(); //очищаем значения всех флагов
    //производим свои манипуляции с потоком
    std::cin.setstate(oldState);//возвращаем поток в первончальное состояние
//Работа с потоком вывода
//Нужно понимать, что весь вывод в объекты типа ostream буферизуется.
//Вывод в cerr - не буферизуется.
//std::endl - сбрасывает буффер
//по умолчанию, cerr и cin связаны с cout, поэтому чтение из потока cin или вывод
//в cerr сбрасывает буффер cout
//Заставить cout сбросить буффер без вызова cin/cerr :
    std::cout << std::endl;
    std::cout << std::ends;
    std::cout << std::flush;
//все эти методы применимы однократно. Если же нужно постоянно сбрасывать cout, лучше использовать
//unitbuf
    std::cout<<std::unitbuf;
//отменяется с помощью
    std::cout<<std::nounitbuf;
    //std::cin.tie(nullptr);//отмены связи cout и cin
    //std::cin.tie(&cerr);//связываем его с cerr
//работа с файлами
//общий тип - fstream
    //std::fstream file;
//открываем файл для ввода с помощью создания экземпляра типа ifstream
    std::ifstream fileInput;
    fileInput.open("file.txt");
//открываем файл для вывода с помощью создания экземпляра типа ofstream
    std::ofstream fileOutput;
    fileOutput.open("file.txt");
//Заметим, что istream - базовый класс для ifstream
//а ostream - базовый для ofstream
//поэтому правильно организованный оператор ввода/вывода работает как с
//стандартными устройствами, так и с файлами

//Не забываем всегда проверять, открылся ли файл!
    if(fileInput && fileInput.is_open())
    {}
    fileInput.close();
    //открыть двоичный файл на чтение с конца
    std::ifstream fileInput2
            ("file.txt", std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
    //открыть двоичный файл на вывод, не удаляя предыдущее содержимое
    std::ofstream fileOutput2
            ("output.txt", std::ostream::out | std::ofstream::binary | std::ofstream::app);
    //открыть двоичный файл на вывод, очистив его
    std::ofstream fileOutput3
            ("output.txt", std::ostream::out | std::ofstream::binary | std::ofstream::trunc);
    //для ofstream trunc и out идут по умолчанию
    //ifstream нельзя указать trunc, ofstream - out
    //при каждом вызове open можно переустанавливать флаги

//Работа с строковыми потоками
    std::string line;
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::string each;
    while(stream >> each)
    {
        std::cout << each;
    }

    std::ostringstream ostringstream;
    int index = 5;
    while(++index < 10)
    {
        std::string in;
        std::cin>>in;
        //если строка валидна, сохраняем в файл
        //иначе кешируем
        if(in.length())
        {
            //
        }
        else
        {
            ostringstream << in;
        }
    }
//=====================================================================================================


//Генерация случайных чисел в С++
//=====================================================================================================
    std::mt19937 variableToUseInRandAlgorithm;
    size_t valueToSeed;
    variableToUseInRandAlgorithm.seed(valueToSeed);

    std::uniform_int_distribution<uint32_t> uint_dist;// Будет выдавать числа до std::numeric_limits<uint>::max
    std::uniform_int_distribution<uint32_t> uint_dist10(0,10); // От 0 до 10
    //нормальное распределение с параметрами - математическое ожидание и стандратное отклонение
    std::normal_distribution<double> normal_dist(1, 0);  // N(mean, standart deviation)
    for(int index = 0; index < 3; index++)
    {
        std::cout << uint_dist(variableToUseInRandAlgorithm) << ' ' <<
                uint_dist10(variableToUseInRandAlgorithm) << ' ' <<
                normal_dist(variableToUseInRandAlgorithm) << std::endl;
    }

    std::random_device seed;
    std::uniform_int_distribution<int> dist(0, 9);
    dist(seed);
//=====================================================================================================




//Использвование верных границ типов с помощью limits
//=====================================================================================================
    constexpr auto intMax = std::numeric_limits<int>::max;//Максимальное значение типа int на данной машине
    constexpr auto doubleEpsilon = std::numeric_limits<double>::epsilon();
    double d1 = 0.2;
    double d2 = 1 / std::sqrt(5) / std::sqrt(5);
    std::cout << std::fixed << std::setprecision(20)
              << "d1=" << d1 << "d2=" << d2 << std::endl;

    if(d1 == d2)
        std::cout << "d1 == d2\n";
    else
        std::cout << "d1 != d2\n";

    auto AlmostEqual = [](double x, double y, double ulp)  {return std::abs(x-y) <= std::numeric_limits<double >::epsilon() * std::abs(x+y) * ulp
                          // unless the result is subnormal
                          || std::abs(x-y) < std::numeric_limits<double >::min();};
    if(AlmostEqual(d1, d2, 2))
    {
        std::cout << "d1 almost equals d2" << std::endl;
    }
    else
    {
        std::cout << "d1 does not almost equal d2" << std::endl;
    }
//=====================================================================================================

//Контейнеры
//=====================================================================================================
    std::vector<int> vec1(10, 1);//вектор из 10 единиц
    std::vector vec2{1,2,3,4,5};
    std::vector<int> vec3;
    std::vector<double> vec4(200); //вектор из двуxста нулей
    std::cout<<vec4[1];
    vec4.push_back(1);
    vec4.size();

    //std::vector::iterator toModifyEnd = vec1.end(); //нет шаблонного параметра, ошибка
    std::vector<int>::iterator iteratorToModifyEnd = vec1.end();
    for(std::vector<int>::iterator toModifyBegin = vec1.begin();
            toModifyBegin != iteratorToModifyEnd;
            toModifyBegin++) //is here a problem?
    {
        *toModifyBegin = 2;
    }
    for(size_t index = 0; index < vec1.size(); index++)
    {
        vec1[index] = index*index;
    }


    auto toIterateEnd = vec1.cend();
    for(auto toIterateBegin = vec1.cbegin();
            toIterateBegin != toIterateEnd; ++toIterateBegin)
    {
        //с помощью константного итератора нельзя менять содержимое коллекции
        //*toIterateBegin = 2;
        std::cout<< *toIterateBegin << ' ';
    }
    std::cout<<std::endl <<"Max size : "<< vec1.max_size() << std::endl;


    //algo
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec1.begin(), vec1.begin() + 2);
    std::max_element(vec1.begin(), vec1.begin() + 2);
    std::random_shuffle(vec1.begin(), vec1.end());
    std::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec1.begin());



    //LIFO
    std::stack<int> stack;
    stack.size();
    stack.push(2);
    stack.empty();
    stack.pop();
    stack.top();

    //FIFO
    std::queue<int> queue;
    queue.size();
    queue.empty();
    queue.push(12);
    queue.pop();
    queue.front();

    //deque
    std::deque<int> deque;
    deque.size();
    deque.front();
    deque.push_back(23);
    deque.insert(deque.begin(), 23);

    //static array
    std::array<int, 20> array;
    array.size();
    array[1] = 1;

    //set
    //повторов не будет, элементы будут упорядочены
    std::set<int> set;
    set.insert(2);
    set.insert(-1);
    set.insert(2333);
    auto vecCompare = [](const std::vector<int> firstVec, const std::vector<int> secondVec)
    {
        return firstVec.size() == secondVec.size() && firstVec == secondVec;
    };
    //можем работать с любым типом, главное перегрузить для него оператор <
    std::set<std::vector<int>> vectorSet;
    vectorSet.insert(vec1);


    //map
    std::map<std::string, int> words;
    words.insert(std::pair<std::string, int>("a", 1));
    std::ifstream inputFile("input.txt");
    if(!inputFile)
    {
        throw std::runtime_error("You haven't got an input.txt to test map!");
    }


    //std::function - оболочка, которая может содержать в себе любой функциональный объект
    std::function<void(std::map<std::string, int>& words, std::ifstream& file)> countWords =
            [](std::map<std::string, int>& words, std::ifstream& file)
            {
                std::string word;
                while(file >> word)
                {
                    auto find = words.find(word);
                    if(find == words.end())
                    {
                        words.insert(std::pair<std::string, int>(word,1));
                    }
                    else
                    {
                        find->second++;
                    }
                }
            };

    std::cout<<std::endl;
    countWords(words, inputFile);
    for(auto iterator = words.begin(); iterator != words.end(); iterator++)
    {
        std::cout << iterator -> first << ' ' << iterator -> second << std::endl;
    }
    std::cout<<std::endl;

    //функторы, указатели на функции, лямбда функции - функциональный объект
    //предикат - функциональный объект, возвращающий значение типа bool
    class Functor
    {
        int divisor;
    public:
        Functor(int x = 1) : divisor{x}{}
        bool operator()(const int& x){ return x % divisor == 0;}
    };
    Functor divisibleByThree(3);
    divisibleByThree(3);//можно вызвать как функцию
    //считаем количество чисел, кратных трем
    auto quantity = std::count_if(vec1.begin(), vec1.end(), divisibleByThree);
    std::transform(vec1.begin(), vec1.end(), vec1.begin(), [](const int& x){ return x+1; });
    std::cout<<std::endl;
    std::for_each(vec1.begin(), vec1.end(), [](const int& x){std::cout<<x<<' ';});
    auto sqrt = [] (double x) { return std::pow(x, 0.5);};
    std::transform(vec1.begin(), vec1.end(), std::ostream_iterator<int, char>(std::cout, " "), sqrt);
    std::cout<<std::endl;
    std::for_each(vec1.begin(), vec1.end(), Print);
    std::generate(vec2.begin(), vec2.end(), std::rand);

    //связывания
    //bind
    auto sum = [](const double & a, const double & b){ return a+b; };
    auto sumPi = std::bind(sum, std::placeholders::_1, std::atan(1)*4);
    std::cout <<std::endl << "2 + Pi = " << sumPi(2) << std::endl;

    //осмысленная привязка
    std::default_random_engine engine;
    std::uniform_int_distribution<int> distribution(0, 10);
    std::function<int()> random = std::bind(distribution, engine);
    for(int n=0; n<10; ++n)
        std::cout << random() << ' ';


    //valaray
    std::valarray <int> numbers{1,2,3};
    numbers.min();
    numbers.max();
    numbers += 1;
    numbers = numbers.apply([](int x){ return x*x;});
    std::cout<<std::endl;
    for(const auto& each : numbers)
    {
        std::cout<<each<<' ';
    }
    std::cout<<std::endl;

    //OutputIt copy( InputIt first, InputIt last, OutputIt d_first );
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout, " "));

    //lists
    std::list<int> bidirectionalList; //двунаправленный
    std::forward_list<int> list; //однонаправленный

    //hash map
    std::unordered_map<std::string, int> hash;
    hash["ola"] = 10;
//=====================================================================================================


    //=====================================================================================================

//=====================================================================================================
}

