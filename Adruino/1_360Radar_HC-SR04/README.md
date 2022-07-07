
 Sử dụng 2 cảm biến siêu âm để phát hiện các đối tượng và quét 0-360 độ, một động cơ Servo nhỏ để xoay cảm biến quét góc 0-180 độ và 180-0 độ, một Arduino để điều khiển. 
Các bước thực hiện:
Thêm thư viện cho cảm biến siêu âm và khai báo chân cho cảm biến.

Trong vòng lặp chính chúng ta sẽ điều khiển hai chiếc Servo để có thể quét được 360 độ.
Ở Servo thứ nhất chúng ta sẽ cho góc quay từ 0-180 độ bằng một vòng lặp for đồng thời đọc giá trị khoảng cách đo được ở cảm biến siêu âm thứ nhất.
Tương tự như Servo thứ nhất, nhưng ở đây chúng ta cho góc quay ngược lại là từ 180-0 độ và đọc cảm biến siêu âm thứ hai.

Tiếp theo chúng ta tạo đế cho Radar có thể đứng và quay được.
Nối dây theo sơ đồ nguyên lý.
Sau khi hoàn thành phần cứng chúng ta tiến hành nạp chương trình cho Arduino và theo dỗi vật cản qua phần mềm Processing.

Linh kiện: 
Arduino nano
Servo sg90
2 cảm biến siêu âm SR04
Phần mềm:
Arduino ide
Processing
Sơ đồ nguyên lý:


