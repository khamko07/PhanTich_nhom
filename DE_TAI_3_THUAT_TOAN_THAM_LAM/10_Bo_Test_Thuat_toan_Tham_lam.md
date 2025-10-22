# 10 Bộ Test - Thuật Toán Tham Lam

## Bài 1: (COINCHANGE) Đổi Tiền Tối Ưu
Lan cần đổi số tiền 67 nghìn đồng bằng ít tờ tiền nhất từ các mệnh giá có sẵn trong ví.

**Yêu cầu**: Nhập các mệnh giá tiền và số tiền cần đổi. In ra số tờ tiền ít nhất cần dùng.

**Input**: 
- Dòng 1: n, amount (số mệnh giá và số tiền cần đổi)
- Dòng 2: n mệnh giá tiền

**Output**: số tờ tiền ít nhất (hoặc -1 nếu không đổi được)

**Ví dụ**:
| Input | Output |
|-------|--------|
| 4 67<br>50 20 10 5 | 3 |

---

## Bài 2: (ACTIVITY) Lựa Chọn Hoạt Động
Minh có danh sách các cuộc họp và muốn tham gia nhiều cuộc họp nhất có thể mà không bị trùng giờ.

**Yêu cầu**: Nhập thời gian bắt đầu và kết thúc của n hoạt động. In ra số hoạt động tối đa có thể chọn.

**Input**: 
- Dòng 1: n (số hoạt động)
- n dòng tiếp theo: start_i end_i

**Output**: số hoạt động tối đa

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>1 3<br>2 4<br>3 5 | 2 |

---

## Bài 3: (KNAPSACK) Cái Túi Phân Số
Hoa có một cái túi và muốn chọn các món đồ để tối đa hóa giá trị mang theo.

**Yêu cầu**: Nhập giá trị và trọng lượng của n vật phẩm, và sức chứa túi. In ra giá trị tối đa.

**Input**: 
- Dòng 1: n capacity
- n dòng tiếp theo: value_i weight_i

**Output**: giá trị tối đa (làm tròn xuống)

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3 15<br>10 5<br>20 10<br>30 15 | 50 |

---

## Bài 4: (SCHEDULE) Lập Lịch Công Việc
Nam cần sắp xếp thứ tự thực hiện các công việc để tối thiểu hóa thời gian chờ đợi.

**Yêu cầu**: Nhập thời gian thực hiện n công việc. In ra tổng thời gian chờ tối thiểu.

**Input**: 
- Dòng 1: n
- Dòng 2: n số nguyên (thời gian các công việc)

**Output**: tổng thời gian chờ tối thiểu

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>3 1 2 | 3 |

---

## Bài 5: (INTERVALS) Phủ Khoảng
Tuấn cần đặt ít điểm nhất để phủ tất cả các khoảng cho trước.

**Yêu cầu**: Nhập n khoảng [start, end]. In ra số điểm tối thiểu cần đặt.

**Input**: 
- Dòng 1: n
- n dòng tiếp theo: start_i end_i

**Output**: số điểm tối thiểu

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>1 3<br>2 4<br>3 5 | 2 |

---

## Bài 6: (MAXPROFIT) Tối Đa Hóa Lợi Nhuận
Thảo có các công việc với thời hạn và lợi nhuận khác nhau, muốn chọn để tối đa hóa lợi nhuận.

**Yêu cầu**: Nhập thời hạn và lợi nhuận của n công việc. In ra lợi nhuận tối đa.

**Input**: 
- Dòng 1: n
- n dòng tiếp theo: deadline_i profit_i

**Output**: lợi nhuận tối đa

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>2 100<br>1 50<br>2 200 | 300 |

---

## Bài 7: (MINCOINS) Số Xu Tối Thiểu
An cần trả tiền bằng số xu ít nhất từ các loại xu có sẵn.

**Yêu cầu**: Nhập các mệnh giá xu và số tiền cần trả. In ra số xu ít nhất.

**Input**: 
- Dòng 1: n amount
- Dòng 2: n mệnh giá xu

**Output**: số xu ít nhất

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3 11<br>1 5 10 | 2 |

---

## Bài 8: (GASSTATION) Trạm Xăng
Linh lái xe đường dài và cần chọn trạm xăng để đổ xăng sao cho số lần dừng là ít nhất.

**Yêu cầu**: Nhập vị trí các trạm xăng và tầm xa xe. In ra số lần dừng tối thiểu.

**Input**: 
- Dòng 1: n distance tank
- Dòng 2: n vị trí trạm xăng

**Output**: số lần dừng tối thiểu (-1 nếu không thể)

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3 100 50<br>25 50 75 | 1 |

---

## Bài 9: (PLATFORM) Sân Ga Tàu
Đức cần bố trí ít sân ga nhất để phục vụ tất cả các chuyến tàu.

**Yêu cầu**: Nhập thời gian đến và đi của n chuyến tàu. In ra số sân ga tối thiểu.

**Input**: 
- Dòng 1: n
- n dòng tiếp theo: arrival_i departure_i

**Output**: số sân ga tối thiểu

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>1 3<br>2 4<br>3 5 | 2 |

---

## Bài 10: (MEETING) Phòng Họp
Mai cần sắp xếp các cuộc họp vào ít phòng nhất sao cho không bị trùng giờ.

**Yêu cầu**: Nhập thời gian bắt đầu và kết thúc n cuộc họp. In ra số phòng tối thiểu.

**Input**: 
- Dòng 1: n
- n dòng tiếp theo: start_i end_i

**Output**: số phòng tối thiểu

**Ví dụ**:
| Input | Output |
|-------|--------|
| 4<br>1 4<br>2 3<br>4 6<br>5 7 | 2 |