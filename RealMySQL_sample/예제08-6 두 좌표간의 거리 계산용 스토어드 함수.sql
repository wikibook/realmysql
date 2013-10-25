DELIMITER ;;

-- // 두 위도 경도 좌표간의 실제 거리를 Km 단위로 계산하는 함수
CREATE DEFINER='admin'@'localhost'
FUNCTION GeoDistance(p_lat1 DOUBLE, p_lon1 DOUBLE, p_lat2 DOUBLE, p_lon2 DOUBLE) 
RETURNS DOUBLE
    SQL SECURITY INVOKER
BEGIN
  DECLARE v_theta DOUBLE;
  DECLARE v_dist DOUBLE;
          
  SET v_theta = p_lon1 - p_lon2;
  SET v_dist = SIN(p_lat1 * PI() / 180.0) * SIN(p_lat2 * PI() / 180.0) +
          COS(p_lat1 * PI() / 180.0) * COS(p_lat2 * PI() / 180.0) * COS(v_theta * PI() / 180.0);
 
  SET v_dist = ACOS(v_dist);
  SET v_dist = v_dist / PI() * 180.0;
  SET v_dist = v_dist * 60 * 1.1515;
  SET v_dist = v_dist * 1.609344;   
     
  RETURN v_dist;
END ;;


DELIMITER ;
