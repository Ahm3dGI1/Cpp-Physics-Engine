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

    // Magnitude
    float Magnitude() const{ return sqrt(x*x + y*y + z*z); }

    // Normalization
    vec3d Normalized() const{ return *this / Magnitude(); }

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

    //Return Transposed matrix
    mat3x3 Transposed() const{
        mat3x3 result;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                result.data[i][j] = data[j][i];
            }
        }
        return result;
    }

    //Transpose this
    void Transpose(){
        *this = Transposed();
    }

    // Identity matrix
    static mat3x3 Identity() {
        mat3x3 identity;
        identity.data[0][0] = 1;
        identity.data[1][1] = 1;
        identity.data[2][2] = 1;
        return identity;
    }

    // Matrix from axis-angle
    static mat3x3 FromAxisAngle(const vec3d& axis, float angle){
        mat3x3 result;
        float c = cos(angle);
        float s = sin(angle);
        float t = 1 - c;
        result.data[0][0] = t * axis.x * axis.x + c;
        result.data[0][1] = t * axis.x * axis.y - s * axis.z;
        result.data[0][2] = t * axis.x * axis.z + s * axis.y;
        result.data[1][0] = t * axis.x * axis.y + s * axis.z;
        result.data[1][1] = t * axis.y * axis.y + c;
        result.data[1][2] = t * axis.y * axis.z - s * axis.x;
        result.data[2][0] = t * axis.x * axis.z - s * axis.y;
        result.data[2][1] = t * axis.y * axis.z + s * axis.x;
        result.data[2][2] = t * axis.z * axis.z + c;
        return result;
    }

    // To quaternion
    Quat ToQuaternion() const{
        float trace = data[0][0] + data[1][1] + data[2][2];
        if(trace > 0){
            float s = 0.5f / sqrt(trace + 1.0f);
            return Quat(0.25f / s, (data[2][1] - data[1][2]) * s, (data[0][2] - data[2][0]) * s, (data[1][0] - data[0][1]) * s);
        }
        else{
            if(data[0][0] > data[1][1] && data[0][0] > data[2][2]){
                float s = 2.0f * sqrt(1.0f + data[0][0] - data[1][1] - data[2][2]);
                return Quat((data[2][1] - data[1][2]) / s, 0.25f * s, (data[0][1] + data[1][0]) / s, (data[0][2] + data[2][0]) / s);
            }
            else if(data[1][1] > data[2][2]){
                float s = 2.0f * sqrt(1.0f + data[1][1] - data[0][0] - data[2][2]);
                return Quat((data[0][2] - data[2][0]) / s, (data[0][1] + data[1][0]) / s, 0.25f * s, (data[1][2] + data[2][1]) / s);
            }
            else{
                float s = 2.0f * sqrt(1.0f + data[2][2] - data[0][0] - data[1][1]);
                return Quat((data[1][0] - data[0][1]) / s, (data[0][2] + data[2][0]) / s, (data[1][2] + data[2][1]) / s, 0.25f * s);
            }
        }
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

// Define the quaternion structure
struct Quat{
    float w, x, y, z;  // Components

    // Constructor
    Quat(float w = 1, float x = 0, float y = 0, float z = 0) : w(w), x(x), y(y), z(z) {}

    // Retrun Normalizated quaternion
    Quat Normalized() const{
        float mag = sqrt(w*w + x*x + y*y + z*z);
        return Quat(w/mag, x/mag, y/mag, z/mag);
    }

    // Normalize this
    void Normalize(){
        *this = Normalized();
    }

    // To matrix
    mat3x3 ToMatrix() const{
        mat3x3 result;
        result.data[0][0] = 1 - 2*y*y - 2*z*z;
        result.data[0][1] = 2*x*y - 2*z*w;
        result.data[0][2] = 2*x*z + 2*y*w;
        result.data[1][0] = 2*x*y + 2*z*w;
        result.data[1][1] = 1 - 2*x*x - 2*z*z;
        result.data[1][2] = 2*y*z - 2*x*w;
        result.data[2][0] = 2*x*z - 2*y*w;
        result.data[2][1] = 2*y*z + 2*x*w;
        result.data[2][2] = 1 - 2*x*x - 2*y*y;
        return result;
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

vec3d operator*(const mat3x3 matrix, const vec3d& vector){
    vec3d result;
    result.x = matrix.data[0][0] * vector.x + matrix.data[0][1] * vector.y + matrix.data[0][2] * vector.z;
    result.y = matrix.data[1][0] * vector.x + matrix.data[1][1] * vector.y + matrix.data[1][2] * vector.z;
    result.z = matrix.data[2][0] * vector.x + matrix.data[2][1] * vector.y + matrix.data[2][2] * vector.z;
    return result;
}