DELIMITER ;;


CREATE PROCEDURE sf_getfactorial(IN p_max INT, OUT p_sum INT)
BEGIN
  SET max_sp_recursion_depth=50; /* 최대 재귀 호출 회수는 50회 */
  SET p_sum=1;

  IF p_max>1 THEN
    CALL sf_decreaseandmultiply(p_max, p_sum);
  END IF;
END;;

CREATE PROCEDURE sf_decreaseandmultiply(IN p_current INT, INOUT p_sum INT)
BEGIN
  SET p_sum=p_sum * p_current;

  IF p_current>1 THEN
    CALL sf_decreaseandmultiply(p_current-1, p_sum);
  END IF;
END;;

CALL sf_getfactorial(10, @factorial);;
SELECT @factorial;;


DELIMITER ;