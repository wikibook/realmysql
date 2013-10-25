CREATE TABLE tb_weather (
  id INT PRIMARY KEY,
  content VARCHAR(255),
  FULLTEXT INDEX (content)
) ENGINE=groonga DEFAULT CHARSET utf8;

INSERT INTO tb_weather VALUES(1, '내일 서울은 맑을 것입니다.');
INSERT INTO tb_weather VALUES(2, '내일 경남 지방은 비가 올 것입니다.');

SELECT * FROM tb_weather WHERE MATCH(content) AGAINST('서울');
