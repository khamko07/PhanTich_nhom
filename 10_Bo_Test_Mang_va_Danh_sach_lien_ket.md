# 10 Bộ Test - Mảng và Danh Sách Liên Kết

## Bài 1: (MAXARRAY) Tìm Phần Tử Lớn Nhất
Lan có một mảng gồm n số nguyên và muốn tìm số lớn nhất trong mảng để so sánh với điểm thi của mình.

**Yêu cầu**: Nhập vào số phần tử n và n số nguyên. In ra số lớn nhất trong mảng.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên (-10^6 ≤ ai ≤ 10^6)

**Output**: một số nguyên là giá trị lớn nhất

**Ví dụ**:
| Input | Output |
|-------|--------|
| 5<br>3 7 2 9 1 | 9 |

---

## Bài 2: (REVERSE) Đảo Ngược Mảng
Minh cần đảo ngược thứ tự các phần tử trong danh sách điểm số để xem xu hướng thay đổi.

**Yêu cầu**: Nhập vào mảng n phần tử. In ra mảng sau khi đảo ngược.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên

**Output**: n số nguyên theo thứ tự đảo ngược

**Ví dụ**:
| Input | Output |
|-------|--------|
| 4<br>1 2 3 4 | 4 3 2 1 |

---

## Bài 3: (RANGESUM) Tổng Mảng Con
Hoa cần tính tổng điểm từ bài kiểm tra thứ l đến bài thứ r để đánh giá kết quả học tập.

**Yêu cầu**: Nhập mảng n phần tử và hai chỉ số l, r. In ra tổng từ vị trí l đến r.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên
- Dòng 3: l r (0 ≤ l ≤ r < n)

**Output**: một số nguyên là tổng từ l đến r

**Ví dụ**:
| Input | Output |
|-------|--------|
| 5<br>1 2 3 4 5<br>1 3 | 9 |

---

## Bài 4: (ADDLIST) Thêm Vào Danh Sách Liên Kết
Nam cần tạo danh sách các nhiệm vụ bằng cách thêm từng nhiệm vụ vào đầu danh sách.

**Yêu cầu**: Nhập n số và thêm vào đầu danh sách liên kết. In ra danh sách cuối cùng.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 100)
- Dòng 2: n số nguyên

**Output**: danh sách sau khi thêm (thứ tự ngược lại)

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>1 2 3 | 3 2 1 |

---

## Bài 5: (SEARCH) Tìm Kiếm Tuyến Tính
Thảo cần tìm vị trí của một số cụ thể trong danh sách điểm danh để kiểm tra.

**Yêu cầu**: Nhập mảng n phần tử và số x cần tìm. In ra vị trí đầu tiên của x (bắt đầu từ 0).

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên
- Dòng 3: x (số cần tìm)

**Output**: vị trí của x (hoặc -1 nếu không tìm thấy)

**Ví dụ**:
| Input | Output |
|-------|--------|
| 5<br>10 20 30 20 40<br>20 | 1 |

---

## Bài 6: (MINARRAY) Tìm Phần Tử Nhỏ Nhất
Tuấn muốn tìm điểm thấp nhất trong bảng điểm để xác định mức cần cải thiện.

**Yêu cầu**: Nhập mảng n phần tử. In ra giá trị nhỏ nhất.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên

**Output**: một số nguyên là giá trị nhỏ nhất

**Ví dụ**:
| Input | Output |
|-------|--------|
| 4<br>5 2 8 1 | 1 |

---

## Bài 7: (SUMARRAY) Tổng Mảng
Linh cần tính tổng tất cả điểm số trong học kỳ để tính điểm trung bình.

**Yêu cầu**: Nhập mảng n phần tử. In ra tổng tất cả phần tử.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên

**Output**: một số nguyên là tổng các phần tử

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>1 2 3 | 6 |

---

## Bài 8: (COUNTEVEN) Đếm Số Chẵn
An cần đếm có bao nhiêu số chẵn trong danh sách số thứ tự ghế ngồi.

**Yêu cầu**: Nhập mảng n phần tử. In ra số lượng phần tử chẵn.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên

**Output**: một số nguyên là số lượng số chẵn

**Ví dụ**:
| Input | Output |
|-------|--------|
| 5<br>1 2 3 4 5 | 2 |

---

## Bài 9: (INSERTPOS) Chèn Phần Tử
Đức cần chèn một số vào vị trí cụ thể trong danh sách để sắp xếp lại thứ tự.

**Yêu cầu**: Nhập mảng n phần tử, vị trí pos và giá trị val. In ra mảng sau khi chèn.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên
- Dòng 3: pos val (0 ≤ pos ≤ n)

**Output**: mảng sau khi chèn val vào vị trí pos

**Ví dụ**:
| Input | Output |
|-------|--------|
| 3<br>1 3 5<br>1 2 | 1 2 3 5 |

---

## Bài 10: (FREQUENCY) Đếm Tần Suất
Mai cần đếm số lần xuất hiện của một số cụ thể trong danh sách để thống kê.

**Yêu cầu**: Nhập mảng n phần tử và số x. In ra số lần xuất hiện của x.

**Input**: 
- Dòng 1: n (1 ≤ n ≤ 1000)
- Dòng 2: n số nguyên
- Dòng 3: x (số cần đếm)

**Output**: một số nguyên là số lần xuất hiện của x

**Ví dụ**:
| Input | Output |
|-------|--------|
| 6<br>1 2 2 3 2 4<br>2 | 3 |