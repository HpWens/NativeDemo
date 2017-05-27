package com.github.asdemo;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private TextView tvNDKStr;

    private Button btnTwoArray;

    static {
        System.loadLibrary("ndk-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tvNDKStr = (TextView) findViewById(R.id.tv_ndk_str);
        btnTwoArray = (Button) findViewById(R.id.btn_two_array);

        initData();
        setListener();
    }

    private void setListener() {

        btnTwoArray.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int[][] twoArray = getNDKTwoArray(2);

                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < twoArray.length; i++) {
                    int[] arr = twoArray[i];
                    for (int j = 0; j < arr.length; j++) {
                        sb.append("--" + arr[j]);
                    }
                    sb.append("\n");
                }

                Toast.makeText(MainActivity.this, sb.toString(), Toast.LENGTH_SHORT).show();
            }
        });

        findViewById(R.id.btn_set_name).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Student student = new Student();
                student.setName("hello word");

                setStudentName(student);

                Toast.makeText(MainActivity.this, "" + student.getName(), Toast.LENGTH_SHORT).show();
            }
        });

        findViewById(R.id.btn_call_back).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(MainActivity.this, "" + callJavaMethod(), Toast.LENGTH_SHORT).show();
            }
        });

        findViewById(R.id.btn_java_obj).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Student student = getNativeStudent();
                Toast.makeText(MainActivity.this, "" + "名字：" + student.getName() + "  年龄：" + student.getAge(), Toast
                        .LENGTH_SHORT).show();
            }
        });

        Student student = new Student();
        student.setName("端午快乐");
        student.setAge(66);
        saveStudentToNative(student);

        findViewById(R.id.btn_array).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ArrayList<Student> lists = getNativeStudents();

                Toast.makeText(MainActivity.this, "" + "集合的第一项名字：" + lists.get(0).getName(), Toast
                        .LENGTH_SHORT).show();
            }
        });

    }

    public String javaMethod(String name, float price, int number) {
        return name + "获得：" + price * number + "¥";
    }

    private void initData() {
        tvNDKStr.setText(getNDKString());
    }

    //获取 native 字符串
    public native String getNDKString();

    //获取int型的二维数组
    public native int[][] getNDKTwoArray(int size);

    //设置实体类 Student 的 name 值
    public native void setStudentName(Student student);

    //回调Java层的方法
    public native String callJavaMethod();

    //native层返回Student对象
    public native Student getNativeStudent();

    //传递java对象到native层
    public native void saveStudentToNative(Student student);

    //Native返回集合对象
    public native ArrayList<Student> getNativeStudents();
}
