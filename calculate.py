import math

# 经纬度数据
cities = {
    "Beijing": (39.9042, 116.4074),
    "Shanghai": (31.2304, 121.4737),
    "Tianjin": (39.3434, 117.3616),
    "Chongqing": (29.5630, 106.5516),
    "Zhengzhou": (34.7466, 113.6254),
    "Wuhan": (30.5928, 114.3055),
    "Nanjing": (32.0603, 118.7969),
    "Hangzhou": (30.2741, 120.1551),
    "Lasa": (29.6520, 91.1175),
    "Guangzhou": (23.1291, 113.2644),
    "Haikou": (20.0440, 110.1999),
    "Shijiazhuang": (38.0428, 114.5149),
    "Shenyang": (41.8057, 123.4315),
    "Xian": (34.3416, 108.9398),
    "Changchun": (43.8171, 125.3235),
    "Hongkong": (22.3193, 114.1694),
    "Guiyang": (26.6470, 106.6302),
    "Kunming": (25.0438, 102.7100),
    "Macao": (22.1987, 113.5439),
    "Harbin": (45.8038, 126.5349),
    "Hefei": (31.8206, 117.2290),
    "Changsha": (28.2282, 112.9388),
    "Taiyuan": (37.8706, 112.5489),
    "Yinchuan": (38.4872, 106.2309),
    "Shenzhen": (22.5431, 114.0579),
    "Chengdu": (30.5728, 104.0668)
}

def haversine(lat1, lon1, lat2, lon2):
    R = 6371  # 地球半径，单位为公里
    dlat = math.radians(lat2 - lat1)
    dlon = math.radians(lon2 - lon1)
    a = math.sin(dlat / 2) ** 2 + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dlon / 2) ** 2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    distance = R * c
    return distance

# 计算所有城市之间的距离
distances = {}
for city1 in cities:
    for city2 in cities:
        if city1 != city2:
            lat1, lon1 = cities[city1]
            lat2, lon2 = cities[city2]
            distance = haversine(lat1, lon1, lat2, lon2)
            distances[(city1, city2)] = distance

# 打印结果
for (city1, city2), distance in distances.items():
    print(f"({city1},{city2}):{distance:.2f} km")
