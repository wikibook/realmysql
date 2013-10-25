DELIMITER ;;

-- // 주어진 위치로부터 반경 몇 Km에 속하는 최소 위도를 계산하는 함수
DROP FUNCTION GetMinLatitude;;
CREATE DEFINER='admin'@'localhost'
FUNCTION GetMinLatitude(p_lon DOUBLE, p_lat DOUBLE, p_radiuskilo FLOAT) 
RETURNS DOUBLE
    NO SQL
    DETERMINISTIC
    SQL SECURITY INVOKER
BEGIN
  RETURN ROUND(p_lat - (p_radiuskilo / 111.2), 4);
END ;;


-- // 주어진 위치로부터 반경 몇 Km에 속하는 최소 경도를 계산하는 함수
DROP FUNCTION GetMinLongitude;;
CREATE DEFINER='admin'@'localhost'
FUNCTION GetMinLongitude(p_lon DOUBLE, p_lat DOUBLE, p_radiuskilo FLOAT) 
RETURNS DOUBLE
    NO SQL
    DETERMINISTIC
    SQL SECURITY INVOKER
BEGIN
  RETURN ROUND(p_lon - (p_radiuskilo / abs(cos(radians(p_lat))*111.2)), 4);
END ;;


-- // 주어진 위치로부터 반경 몇 Km에 속하는 최대 위도를 계산하는 함수
DROP FUNCTION GetMaxLatitude;;
CREATE DEFINER='admin'@'localhost'
FUNCTION GetMaxLatitude(p_lon DOUBLE, p_lat DOUBLE, p_radiuskilo FLOAT) 
RETURNS DOUBLE
    NO SQL
    DETERMINISTIC
    SQL SECURITY INVOKER
BEGIN
  RETURN ROUND(p_lat + (p_radiuskilo / 111.2), 4);
END ;;


-- // 주어진 위치로부터 반경 몇 Km에 속하는 최대 경도를 계산하는 함수
DROP FUNCTION GetMaxLongitude;;
CREATE DEFINER='admin'@'localhost'
FUNCTION GetMaxLongitude(p_lon DOUBLE, p_lat DOUBLE, p_radiuskilo FLOAT) 
RETURNS DOUBLE
    NO SQL
    DETERMINISTIC
    SQL SECURITY INVOKER
BEGIN
  RETURN ROUND(p_lon + (p_radiuskilo / abs(cos(radians(p_lat))*111.2)), 4);
END ;;

DELIMITER ;


