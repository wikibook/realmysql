CREATE TABLE tb_tritonn (
  doc_id INT NOT NULL AUTO_INCREMENT,
  doc_title VARCHAR(1000) NOT NULL,
  doc_body TEXT,
  PRIMARY KEY (doc_id),
  FULLTEXT INDEX fx_document USING NGRAM, NO NORMALIZE (doc_body)
) ENGINE=MyISAM DEFAULT CHARSET UTF8;

INSERT INTO tb_tritonn VALUES 
         (NULL, 'Tritonn full text search engine', '트리튼 전문 검색 엔진');
