import pandas as pd
import matplotlib.pyplot as plt
import matplotlib

matplotlib.rcParams['font.sans-serif'] = ['Microsoft YaHei']

# 读取数据，将第一列作为索引
df = pd.read_csv('1.csv', index_col=0)
# df = pd.read_csv('2.csv', index_col=0)

# 转置数据框，使每个consumer成为一列，时间点成为行
df = df.transpose()

# 设置图表大小和标题
plt.figure(figsize=(10, 6))
plt.title('傳送速率與 Consumer 數量對封包的影響')
# plt.title('Buffer Size 與 Consumer 數量對封包的影響')

# 绘制每条折线
for consumer in df.columns:
    plt.plot(df.index, df[consumer], label=consumer, marker='o')

plt.ylim([0, 100])

# 设置图例位置
plt.legend()

# 设置X轴和Y轴标题
plt.xlabel('傳送速率 (ms)')
# plt.xlabel('buffer size')
plt.ylabel('loss rate (%)')

# 显示图表
#plt.show()
plt.savefig('1.png')
# plt.savefig('2.png')