// math.h

// Define the vec3d structure
struct vec3d{
    public:

    float x, y, z;  // Coordinates

    // Constructor
    vec3d(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    // Operator overloads for vector arithmetic
    vec3d operator+(const vec3d& v) const{ return vec3d(x+v.x, y+v.y, z+v.z); }
    vec3d operator-(const vec3d& v) const{ return vec3d(x-v.x, y-v.y, z-v.z); }
    void operator+=(const vec3d& v){ x += v.x; y += v.y; z += v.z; }
    void operator-=(const vec3d& v){ x -= v.x; y -= v.y; z -= v.z; }
    vec3d operator*(const float scalar) const{ return vec3d(x*scalar, y*scalar, z*scalar); }
    vec3d operator/(const float scalar) const{ return vec3d(x/scalar, y/scalar, z/scalar); }
    void operator*=(const float scalar){ x *= scalar; y *= scalar; z *= scalar; }
    void operator/=(const float scalar){ x /= scalar; y /= scalar; z /= scalar; }

    // Dot product
    float operator*(const vec3d& v) const{ return x*v.x + y*v.y + z*v.z; }

    // Cross product
    vec3d operator%(const vec3d& v) const{ return vec3d(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }

    // Matrix multiplication
    vec3d operator*(const mat3x3& matrix) const{
        vec3d result;
        result.x = x * matrix.data[0][0] + y * matrix.data[1][0] + z * matrix.data[2][0];
        result.y = x * matrix.data[0][1] + y * matrix.data[1][1] + z * matrix.data[2][1];
        result.z = x * matrix.data[0][2] + y * matrix.data[1][2] + z * matrix.data[2][2];
        return result;
    }

    // Outer product
    mat3x3 OuterProduct(const vec3d& v) const{
        mat3x3 result;
        result.data[0][0] = x * v.x; result.data[0][1] = x * v.y; result.data[0][2] = x * v.z;
        result.data[1][0] = y * v.x; result.data[1][1] = y * v.y; result.data[1][2] = y * v.z;
        result.data[2][0] = z * v.x; result.data[2][1] = z * v.y; result.data[2][2] = z * v.z;
        return result;
    }

    // Zero vector
    vec3d Zero(){ x = 0; y = 0; z = 0; return *this; }
};

// Define the mat3x3 structure
struct mat3x3{
    float data[3][3] = {0};  // Matrix data

    // Operator overloads for matrix arithmetic
    mat3x3 operator+(const mat3x3& m) const{
        mat3x3 result;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                result.data[i][j] = data[i][j] + m.data[i][j];
            }
        }
        return result;
    }

    mat3x3 operator-(const mat3x3& m) const{
        mat3x3 result;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                result.data[i][j] = data[i][j] - m.data[i][j];
            }
        }
        return result;
    }

    mat3x3 operator*(const float scalar) const{
        mat3x3 result;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    mat3x3 operator/(const float scalar) const{
        mat3x3 result;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                result.data[i][j] = data[i][j] / scalar;
            }
        }
        return result;
    }

    void operator+=(const mat3x3& m){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                data[i][j] += m.data[i][j];
            }
        }
    }

    // Identity matrix
    static mat3x3 Identity() {
        mat3x3 identity;
        identity.data[0][0] = 1;
        identity.data[1][1] = 1;
        identity.data[2][2] = 1;
        return identity;
    }

    // Zero matrix
    void Zero(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                data[i][j] = 0;
            }
        }
    }
};

// Scalar multiplication
mat3x3 operator*(const float scalar, const mat3x3& matrix){
    mat3x3 result;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            result.data[i][j] = matrix.data[i][j] * scalar;
        }
    }
    return result;
}