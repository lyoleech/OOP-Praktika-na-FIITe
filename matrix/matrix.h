#pragma once


//sl headers
//==============================================================================
#include <array>
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <functional>
#include <type_traits>
#include <cmath>
//==============================================================================

//my headers
//==============================================================================
#include "exception.h"
#include "fraction.h"
//==============================================================================

//my defines
//==============================================================================
//==============================================================================

//class template declaration
//==============================================================================
template <typename Type, size_t dim = 100, typename enable = void>
class matrix;
//==============================================================================

//typedefs and usings
//==============================================================================
template <typename Type>
using floatingOrIntegralChecking = typename
std :: enable_if<std::is_floating_point<Type>::value
||
std::is_integral<Type>::value
||
std :: is_same<Type, fraction<int>> :: value>::type;
//==============================================================================


//class definition
//==============================================================================
template <typename Type, size_t dim>
class matrix
<Type,dim, floatingOrIntegralChecking<Type>>
{
//class usings
//==============================================================================
    template <typename type, size_t dimension>
    using matarray = std::array<std :: array <type, dimension> , dim>;
//==============================================================================
public :
//constructors
//==============================================================================
        matrix();
        matrix (const matrix <Type, dim> &other);
        matrix (const matarray<Type, dim> &other);
        explicit matrix(const std :: initializer_list <Type> &other);
        matrix(const Type other[][dim], const size_t otherLines, const size_t otherColumns);
//==============================================================================

//get data
//==============================================================================
    constexpr size_t Dimension() const noexcept {return dimension;}
    constexpr size_t size() const noexcept {return dimension*dimension;}
    void print(std:: ostream &output) const noexcept;
//==============================================================================

//operators to work with matrixes
//==============================================================================
    matrix<Type,dim>& operator += (const matrix<Type,dim> &other);
    matrix<Type,dim>& operator += (const Type &other);

    matrix<Type,dim>& operator -= (const matrix<Type,dim> &other);
    matrix<Type,dim>& operator -= (const Type &other);

    matrix<Type,dim>& operator *= (const matrix<Type,dim> &other);
    matrix<Type,dim>& operator *= (const Type &other);

    matrix<Type,dim>& operator /= (const matrix<Type,dim> &other);

    matrix <Type, dim>& operator = (const std :: initializer_list <Type> &other);

    matrix<Type,dim> operator -(); //unary minus
    matrix <Type, dim>& operator ++ ();

    bool operator ! ();
//==============================================================================

//public methods
//==============================================================================
    Type determinant() const;
    Type trace() noexcept;
    matrix <Type, dim> inverse() const;
    Type getElement (const size_t row = 0, const size_t column = 0) const;
//==============================================================================

//friend operators
//==============================================================================
//==============================================================================

//class typedefs
//==============================================================================
    using MatrixType = Type;
//==============================================================================
private :
//private data
//==============================================================================
    size_t dimension = dim;
    std::array<std :: array <Type, dim> , dim> Matrix;
//==============================================================================

//private methods
//==============================================================================
    //Get Data
    //==============================================================================
        std::array<Type, dim>& Column(const size_t column) noexcept {return Matrix[column];}
        const std::array<Type, dim>& Column(const size_t column) const noexcept {return Matrix[column];}
        Type& element(const size_t column, const size_t row) {return Matrix[column][row];}
    //==============================================================================
    void doSometingWithElement(std :: function<void (const size_t, const size_t)> operation);
    void fillStdMatrix(matarray<Type,dim> &matrixTofill, const Type &value)const;
    void makeDiagFromStdMatrix(matarray<Type,dim> &matrixTofill, const Type &value = 1)const;
    void outMatArray(matarray<Type,dim> &matrixToOutput)const;
//==============================================================================

//exceptions which this class can throw
//==============================================================================
    dEXCEPTION(TooLessArgumentsInInitializerList);
    dEXCEPTION(indexOutOfRange);
    dEXCEPTION(TooManyArgumentsInInitializerList);
    dEXCEPTION(MatrixesSizesAreNotEqual);
    dEXCEPTION(OperationWithNotEqualMatrixes);
    dEXCEPTION(determinantCannotBeCountedForThisTypeOfMatrixElement);
    dEXCEPTION(DeterminantIsZeroAndInverseCanNotBeCalculated);
//==============================================================================
};
//==============================================================================


//realization of the constructors
//==============================================================================
template <typename Type, size_t dim>
matrix<Type,dim,floatingOrIntegralChecking<Type>>:: matrix()
{
    doSometingWithElement(
    [&](const size_t column, const size_t row)
    {if(row==column){Matrix[column][row]=1;} else {Matrix[column][row]=0;}});
}

template <typename Type, size_t dim>
matrix<Type,dim,floatingOrIntegralChecking<Type>>:: matrix(const matrix <Type, dim> &other)
{
    if (Dimension() == other.Dimension())
    {
        for (size_t column{0}; column < Dimension(); column++)
        {
            std::copy(other.Column(column).begin(), other.Column(column).end(), Column(column).begin());
        }
    }
    else
    {
        throw MatrixesSizesAreNotEqual("MATRIX : Matrix can not be constructed because the size of the initialize's matrix is not equal to its size!");
    }
}

template <typename Type, size_t dim>
matrix<Type,dim,floatingOrIntegralChecking<Type>>:: matrix(const std :: initializer_list <Type> &other)
{
    if (other.size() == size())
    {
        auto element{other.begin()};
        doSometingWithElement(
        [&](const size_t column, const size_t row)
        {    Matrix[column][row] = *element; element++;}
        );
    }
    else if (other.size() < size())
    {
        throw TooLessArgumentsInInitializerList("MATRIX : Too less arguments in initializer list!");
    }
    else
    {
        throw TooManyArgumentsInInitializerList("MATRIX : Too many arguments in initializer list!");
    }
}


template <typename Type, size_t dim>
matrix<Type,dim,floatingOrIntegralChecking<Type>>:: matrix(const Type other[][dim], const size_t otherLines, const size_t otherColumns)
{
    if (Dimension() == otherLines && Dimension() == otherColumns)
    {
        doSometingWithElement(
        [&](const size_t column, const size_t row)
        {Matrix[column][row] = other[row][column];});
    }
    else
    {
        throw MatrixesSizesAreNotEqual("MATRIX : Matrix can not be constructed because the size of the initialize's matrix is not equal to its size!");
    }
}

template <typename Type, size_t dim>
matrix<Type,dim,floatingOrIntegralChecking<Type>>::matrix (const matarray<Type, dim> &other) :
Matrix{other}{}
//==============================================================================


//realization of the operators to work with matrixes
//==============================================================================
template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator += (const matrix<Type,dim> &other)
{
    if (Dimension() == other.Dimension())
    {
        doSometingWithElement(
        [&](const size_t column, const size_t row)
        {Matrix[column][row]+=other.Column(column)[row];}
        );
        return *this;
    }
    else
    {
        throw OperationWithNotEqualMatrixes("MATRIX : you can not operate with not equal matrxies!");
    }
}

template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator += (const Type &other)
{
    doSometingWithElement(
    [&](const size_t column, const size_t row)
    {Matrix[column][row] += other;});
    return *this;
}

template <typename Type, size_t dim>
matrix<Type,dim> matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator - ()
{
    matrix<Type,dim> oppositeMatrix;
    doSometingWithElement(
    [&](const size_t column,const size_t row)
    {oppositeMatrix.Column(column)[row] = -Matrix[column][row];}
    );
    return oppositeMatrix;
}

template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator -= (const matrix<Type,dim> &other)
{
    if (Dimension() == other.Dimension())
    {
        doSometingWithElement(
        [&](const size_t column, const size_t row){Matrix[column][row]-=other.Column(column)[row];});
    }
    else
    {
        throw OperationWithNotEqualMatrixes("MATRIX : you can not operate with not equal matrxies!");
    }
    return *this;
}

template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator -= (const Type &other)
{
    doSometingWithElement(
    [&](const size_t column, const size_t row){Matrix[column][row]-=other;});
    return *this;
}

template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator *= (const matrix<Type,dim> &other)
{
    matrix<Type,dim> temporary;
    doSometingWithElement(
    [&](const size_t column, const size_t row)
    {
        Type sum{0};
        size_t resultColumn{0};
        for(; resultColumn < Dimension(); ++resultColumn)
        {
            sum += Matrix[resultColumn][row]*other.Column(column)[resultColumn];
        }

        temporary.Column(column)[row] = sum;
    });
    return *this = temporary;
}


template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator *= (const Type &other)
{
     doSometingWithElement(
     [&](const size_t column, const size_t row){Matrix[column][row]*=other;});
     return *this;
 }

 template <typename Type, size_t dim>
 matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator = (const std :: initializer_list <Type> &other)
{
    if (other.size() != size())
    {
        throw TooLessArgumentsInInitializerList("MATRIX : Here are to less arguments in initializer list!");
    }
    else
    {
        auto current{other.begin()};
         doSometingWithElement(
         [&](const size_t column, const size_t row)
         {Matrix[column][row]=*current;current++;});
         return *this;
    }
}

template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>:: operator /= (const matrix<Type,dim> &other)
{
    matrix<Type,dim> inverse{other.inverse()};
    return *this*=inverse;
}

template <typename Type, size_t dim>
Type matrix<Type, dim,floatingOrIntegralChecking<Type>>::getElement (const size_t row, const size_t column) const
{
    if (column >= Dimension() || row >= Dimension())
    {
        throw indexOutOfRange("Dimension of matrix is less than index!");
    }
    return Matrix[column][row];
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator + (const matrix<Type, dim> &first, const matrix<Type, dim> &other)
{
    matrix<Type, dim> result{first};
    return result += other;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator - (const matrix<Type, dim> &first, const matrix<Type, dim> &other)
{
    matrix<Type, dim> result{first};
    return result -= other;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator * (const matrix<Type, dim> &first, const matrix<Type, dim> &other)
{
    matrix<Type, dim> result{first};
    result *= other;
    return result;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator * (const matrix<Type, dim> &first, const Type &other)
{
    matrix<Type, dim> result{first};
    return result *= other;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator * (const Type &other, const matrix<Type, dim> &first)
{
    matrix<Type, dim> result{first};
    return result *= other;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator * (const matrix<Type, dim> &first,const fraction<int> &other)
{
    matrix<Type, dim> result{first};
    return result *= other;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator * (const fraction<int> &other, const matrix<Type, dim> &first)
{
    matrix<Type, dim> result{first};
    return result *= other;
}

template <typename Type, size_t dim>
matrix<Type,dim>& matrix<Type,dim,floatingOrIntegralChecking<Type>>::
operator ++ ()
{
    doSometingWithElement(
    [&](const size_t column, const size_t row)
    {Column(column)[row]++;});
    return *this;
}

template <typename Type, size_t dim>
bool matrix<Type,dim,floatingOrIntegralChecking<Type>>::operator ! ()
{
    bool flag{true};
    constexpr double epsilon{1e-11};
    doSometingWithElement([&](const size_t column, const size_t row){if (static_cast<double>(Matrix[row][column]) - epsilon > 0){flag = false;}});
    return flag;
}

template <typename Type, size_t dim>
matrix<Type,dim>
operator ++ (const matrix<Type, dim> &other, int postfix)
{
    matrix<Type, dim> result{other};
    return result+=postfix=1;
}

template <typename Type, size_t dim>
std :: ostream& operator << (std :: ostream &output,const matrix <Type, dim> &other)
{
     other.print(output);
     return output;
}

template <typename Type, size_t dim>
bool operator < (const matrix<Type, dim> &other, int)
{
    return false;
}

template <typename Type, size_t dim>
bool operator > (const matrix<Type, dim> &other, int)
{
    return true;
}

template <typename Type, size_t dim>
bool operator == (const matrix<Type, dim> &other, const Type &value)
{
    bool flag{true};

    for(size_t row{0}; row < other.Dimension(); row++)
    {
        for(size_t column{0}; column < other.Dimension(); column++)
        {
            if(column == row)
            {
                if (other.getElement(row,column) != value)
                {
                    flag = false;
                    break;
                }
            }
            else
            {
                if (other.getElement(row,column) != 0)
                {
                    flag = false;
                    break;
                }
            }
        }
    }

    return flag;
}

//==============================================================================

//realization of the private methods
//==============================================================================
template <typename Type, size_t dim>
void matrix<Type,dim,floatingOrIntegralChecking<Type>>::
print(std:: ostream &output) const noexcept
{
    for (size_t row  {0}; row < Dimension(); ++row)
    {
        for (size_t column {0}; column < Dimension(); ++column)
        {
            output << Matrix[column][row] << ' ';
        }
        output << std :: endl;
    }
}

template <typename Type, size_t dim>
void matrix<Type,dim,floatingOrIntegralChecking<Type>>::
doSometingWithElement(std :: function<void (const size_t, const size_t)> operation)
{
    for(size_t row{0}; row < Dimension(); row++)
    {
        for(size_t column{0}; column < Dimension(); column++)
        {
            operation(column,row);
        }
    }
}

template <typename Type, size_t dim>
void matrix<Type, dim, floatingOrIntegralChecking<Type>>::fillStdMatrix(matarray<Type,dim> &matrixTofill,const Type &value) const
{
    for(auto &column : matrixTofill)
    {
        for(auto &element : column)
        {
            element = value;
        }
    }
}

template <typename Type, size_t dim>
void matrix<Type, dim, floatingOrIntegralChecking<Type>>::makeDiagFromStdMatrix(matarray<Type,dim> &matrixTofill, const Type &value) const
{
    const size_t size{matrixTofill.size()};
    for(size_t row{0}; row < size; row++)
    {
        for(size_t column{0}; column < size; column++)
        {
            if (row == column)
            {
                matrixTofill[column][row] = value;
            }
            else
            {
                matrixTofill[column][row] = 0;
            }
        }
    }
}

template <typename Type, size_t dim>
void matrix<Type,dim,floatingOrIntegralChecking<Type>>::outMatArray(matarray<Type,dim> &matrixToOutput) const
{
    auto outLine = [&](const size_t row)
    {for(size_t column{0}; column<Dimension();column++)
    {std::cout<<matrixToOutput[column][row]<<' ';}
    };

    auto outMatrix = [&]()
    {for(size_t row{0};row<Dimension();row++)
    {outLine(row);std::cout<<std::endl;}};
    outMatrix();
}
//==============================================================================

//realization of the public methods
//==============================================================================
template <typename Type, size_t dim>
Type matrix<Type,dim,floatingOrIntegralChecking<Type>>:: determinant() const
{
    Type result{ 1 };
    constexpr double epsilon{ 1e-9 };
    matarray<Type, dim> copyMatrix{Matrix};

    for (size_t determinantLine{0}; determinantLine < Dimension(); determinantLine++)
    {
        if (fabs(static_cast <double>(copyMatrix[determinantLine][determinantLine])) - epsilon < 0)
        {
            size_t lines{determinantLine+1};
            for(; lines < Dimension(); lines++)
            {
                if(abs(static_cast <double>(copyMatrix[determinantLine][lines])) - epsilon > 0)
                {
                    break;
                }
            }
            if (lines == Dimension())
            {
                result = 0;
                break;
            }
            else
            {
                result *= -1;
                for(size_t column{0}; column < Dimension(); column++)
                {
                    std::swap(copyMatrix[column][lines], copyMatrix[column][determinantLine]);
                }
            }
        }//If main element is zero


        result *= copyMatrix[determinantLine][determinantLine];

        for(size_t lines{determinantLine+1}; lines < Dimension(); lines++)
        {
            if (fabs(static_cast <double>(copyMatrix[determinantLine][lines])) - epsilon > 0)
            {
                Type temporary {copyMatrix[determinantLine][lines]
                    /
                    copyMatrix[determinantLine][determinantLine]};
                for(size_t column{determinantLine}; column < Dimension(); column++)
                {
                    copyMatrix[column][lines] -= copyMatrix[column][determinantLine]
                    *
                    temporary;
                }
            }
        }
    }

    return result;
}

template <typename Type, size_t dim>
matrix <Type, dim> matrix<Type, dim,floatingOrIntegralChecking<Type>>::inverse() const
{
    constexpr double epsilon{ 1e-9 };
    if (std::fabs(determinant()) - epsilon < 0)
    {
        throw DeterminantIsZeroAndInverseCanNotBeCalculated("MATRIX : Inverse matrix can not be calculated for the matrix with zero determinant!");
    }

    matrix::matarray<Type, dim> copied{Matrix};
    matrix::matarray<Type, dim> result;
    makeDiagFromStdMatrix(result);

    for(size_t currentLine{0}; currentLine < Dimension(); currentLine++)
    {
        if(std :: fabs(static_cast<double>(copied[currentLine][currentLine])) - epsilon < 0)
        {
            size_t lines{currentLine+1};
            for(; lines <  Dimension(); lines++)
            {
                if(std::fabs(static_cast<double>(copied[currentLine][lines])) - epsilon > 0)
                {
                    break;
                }
            }
            for(size_t column{0}; column < Dimension(); column++)
            {
                std::swap(copied[column][currentLine], copied[column][lines]);
                std::swap(result[column][currentLine], result[column][lines]);
            }
        }

        for(size_t lines{currentLine+1}; lines < Dimension(); lines++)
        {
            if(std::fabs(static_cast<double>(copied[currentLine][lines])) - epsilon > 0)
            {
                Type temporary{copied[currentLine][lines]/copied[currentLine][currentLine]};

                for(size_t column{0}; column < Dimension(); column++)
                {
                    copied[column][lines] -= copied[column][currentLine]*temporary;
                    result[column][lines] -= result[column][currentLine]*temporary;
                }
            }
        }
    }

    for(int currentLine{static_cast <int>(Dimension())-1}; currentLine >= 0; currentLine--)
    {
        for(int lines{currentLine - 1}; lines >= 0; lines--)
        {
            if(std::fabs(static_cast<double>(copied[currentLine][lines])) - epsilon > 0)
            {
                Type temporary{copied[currentLine][lines]/copied[currentLine][currentLine]};
                for(size_t column{0}; column < Dimension(); column++)
                {
                    copied[column][lines] -= copied[column][currentLine] * temporary;
                    result[column][lines] -= result[column][currentLine] * temporary;
                }
            }
        }
    }
    for(size_t row{0}; row < Dimension(); row++)
    {
        for(size_t column{0}; column < Dimension(); column++)
        {
            result[column][row] /= copied[row][row];
        }
    }

    return matrix(result);
}

template <typename Type, size_t dim>
Type matrix<Type,dim,floatingOrIntegralChecking<Type>>::trace() noexcept
{
    Type result{0};
    doSometingWithElement(
    [&](const int &row, const int &column)
    {
        if(row == column){result+=Matrix[row][column];}
    }
    );
    return result;
}
//==============================================================================

//friend operators
//==============================================================================


//==============================================================================
