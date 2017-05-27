#include <jni.h>
#include <string>

#include<android/log.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_github_asdemo_MainActivity_getNDKString(JNIEnv *env, jobject instance) {

    // TODO
    jstring str = env->NewStringUTF("hello word");

    jclass strClass = env->FindClass("java/lang/String");

    return str;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_github_asdemo_MainActivity_getNDKTwoArray(JNIEnv *env, jobject instance, jint size) {
    // TODO
    //获取一维数组 的类引用  jintArray类型
    jclass intArrayClass = env->FindClass("[I");

    //构造一个指向jintArray类一维数组的对象数组，该对象数组初始大小为size
    jobjectArray objectIntArray = env->NewObjectArray(size, intArrayClass, NULL);

    //构建dimion个一维数组，并且将其引用赋值给obejctIntArray对象数组
    for (int i = 0; i < size; i++) {

        //构建 jintArray 一维数组
        jintArray intArray = env->NewIntArray(3);

        //初始化一个容器，假设 大小  = size ;
        jint temp[3];

        for (int j = 0; j < 3; j++) {
            temp[j] = i * 2 + j;
        }

        //给intArray数组设置值
        env->SetIntArrayRegion(intArray, 0, 3, temp);

        //给objectIntArray对象数组赋值，即保持对jint一维数组的引用
        env->SetObjectArrayElement(objectIntArray, i, intArray);

        //删除局部引用
        env->DeleteLocalRef(intArray);
    }
    return objectIntArray;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_github_asdemo_MainActivity_setStudentName(JNIEnv *env, jobject instance, jobject student) {

    // TODO
    //获得Java层该对象实例的类引用，即Student类引用
    jclass studentClass = env->GetObjectClass(student);

    //获得属性句柄     等同于 env->FindClass("java/lang/String")
    jfieldID nameFieldId = env->GetFieldID(studentClass, "name", "Ljava/lang/String;");

    if (nameFieldId == NULL) {
        //__android_log_print(ANDROID_LOG_DEBUG, "-------", "", NULL); //打印字符串
        return;
    }

    //获取该属性的值  注意第一个参数传入的是jobject obj对象
    jstring nameStr = (jstring) env->GetObjectField(student, nameFieldId);

    const char *c_name = env->GetStringUTFChars(nameStr, NULL);

    //打印字符串
    __android_log_print(ANDROID_LOG_DEBUG, "-------", c_name, NULL);

    env->ReleaseStringUTFChars(nameStr, c_name);

    //给name字段设置新值

    char *c_new_name = "i am new name";

    jstring cName = env->NewStringUTF(c_new_name);

    env->SetObjectField(student, nameFieldId, cName);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_github_asdemo_MainActivity_callJavaMethod(JNIEnv *env, jobject instance) {
    // TODO
    //获得Java层该对象实例的类引用，即MainActivity类引用
    jclass activityClass = env->GetObjectClass(instance);

    //获取到方法的(句柄)域ID
    jmethodID javaMethodFieldId = env->GetMethodID(activityClass, "javaMethod",
                                                   "(Ljava/lang/String;FI)Ljava/lang/String;");

    if (javaMethodFieldId == NULL) {
        return env->NewStringUTF("error");
    }
    //设置名称
    jstring name_str = env->NewStringUTF("wen shu");
    //单价
    jfloat price = 55.88f;
    //数量
    jint number = 8;
    //获取返回值
    jstring str = (jstring) env->CallObjectMethod(instance, javaMethodFieldId, name_str, price, number);

    return str;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_github_asdemo_MainActivity_getNativeStudent(JNIEnv *env, jobject instance) {

    // TODO
    //获取类的引用 com/github/asdemo/Student
    jclass studentClass = env->FindClass("com/github/asdemo/Student");

    //获取该类的构造方法 函数名为 <init> 返回类型必须为 void 即 V
    jmethodID constructMethodId = env->GetMethodID(studentClass, "<init>", "(Ljava/lang/String;I)V");

    jstring name = env->NewStringUTF("王者荣耀");

    jint age = 30;

    //创建一个新的对象
    jobject newObj = env->NewObject(studentClass, constructMethodId, name, age);

    return newObj;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_github_asdemo_MainActivity_saveStudentToNative(JNIEnv *env, jobject instance, jobject student) {

    // TODO
    //获取到类的引用
    jclass stu_cls = env->GetObjectClass(student);

    if (stu_cls == NULL) {
        //__android_log_print(ANDROID_LOG_DEBUG, "-------", "", NULL);//打印信息
        return;
    }

    //获取name属性的引用
    jfieldID nameFieldID = env->GetFieldID(stu_cls, "name", "Ljava/lang/String;");

    jfieldID ageFieldID = env->GetFieldID(stu_cls, "age", "I");

    //获取name属性值
    jstring name = (jstring) env->GetObjectField(student, nameFieldID);

    jint age = env->GetIntField(student, ageFieldID);

    const char *c_name = env->GetStringUTFChars(name, NULL);

    __android_log_print(ANDROID_LOG_DEBUG, "-------", c_name, NULL);

    __android_log_print(ANDROID_LOG_DEBUG, "-------", "%d", age, NULL);

    //释放引用
    env->ReleaseStringUTFChars(name, c_name);
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_github_asdemo_MainActivity_getNativeStudents(JNIEnv *env, jobject instance) {

    // TODO
    //获取集合类的引用
    jclass list_cls = env->FindClass("java/util/ArrayList");

    if (list_cls == NULL) {
        //空处理
    }

    //获取集合的构造函数ID
    jmethodID list_construct = env->GetMethodID(list_cls, "<init>", "()V");

    //获取集合对象
    jobject list_obj = env->NewObject(list_cls, list_construct);

    //获取 ArrayList 的 add 方法
    // public boolean add(E e)
    // E表示泛型可以用Object代替
    jmethodID list_add = env->GetMethodID(list_cls, "add", "(Ljava/lang/Object;)Z");

    //获取到Student类
    jclass stu_cls = env->FindClass("com/github/asdemo/Student");
    //获取Student的构造函数ID
    jmethodID stu_construct = env->GetMethodID(stu_cls, "<init>", "(Ljava/lang/String;I)V");

    //添加集合元素
    for (int i = 0; i < 3; i++) {
        jstring name = env->NewStringUTF("端午快乐");
        jint age = 66;
        //调用该对象的构造函数来new一个Student实例
        jobject stu_obj = env->NewObject(stu_cls, stu_construct, name, age);

        //添加集合数据 添加一个Student对象
        env->CallBooleanMethod(list_obj, list_add, stu_obj);
    }

    return list_obj;
}