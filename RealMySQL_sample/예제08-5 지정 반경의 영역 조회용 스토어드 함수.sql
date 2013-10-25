DELIMITER ;;

-- // 주어진 위치로부터 반경 몇 Km에 해당하는 영역(Polygon)을 리턴하는 함수
DROP FUNCTION GetRadianPolygon;;
CREATE DEFINER='admin'@'localhost'
FUNCTION GetRadianPolygon(p_lon DOUBLE, p_lat DOUBLE, p_radiuskilo FLOAT) 
RETURNS VARCHAR(100)
    NO SQL
    DETERMINISTIC
    SQL SECURITY INVOKER
BEGIN
  DECLARE v_min_lat FLOAT DEFAULT 0;
  DECLARE v_min_lon FLOAT DEFAULT 0;
  DECLARE v_max_lat FLOAT DEFAULT 0;
  DECLARE v_max_lon FLOAT DEFAULT 0; 
  SET v_min_lat = GetMinLatitude(p_lon,p_lat,p_radiuskilo);
  SET v_min_lon = GetMinLongitude(p_lon,p_lat,p_radiuskilo);
  SET v_max_lat = GetMaxLatitude(p_lon,p_lat,p_radiuskilo);
  SET v_max_lon = GetMaxLongitude(p_lon,p_lat,p_radiuskilo);

  RETURN
    CONCAT('POLYGON((',
      v_min_lat, ' ', v_min_lon, ',',
      v_min_lat, ' ', v_max_lon, ',',
      v_max_lat, ' ', v_max_lon, ',',
      v_max_lat, ' ', v_min_lon, ',',
      v_min_lat, ' ', v_min_lon, '))');
END ;;

-- // 이 스토어드 함수를 실행해보면 아래와 같은 결과를 받을 수 있다. 
mysql> SELECT GetRadianPolygon(137.2164, 34.9981, 5);;

DELIMITER ;
