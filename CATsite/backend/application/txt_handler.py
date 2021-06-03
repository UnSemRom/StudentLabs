from nltk import word_tokenize as tokenize
from nltk.corpus import stopwords
from nltk.probability import FreqDist
from nltk.stem import WordNetLemmatizer
from nltk.corpus import wordnet
from nltk import pos_tag
from nltk.tokenize import sent_tokenize

import base64
import os

from pymorphy2 import MorphAnalyzer as MorphAnalyzer_rus

from sklearn.feature_extraction.text import TfidfVectorizer,CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity

import pandas as pd

from scipy.spatial import distance

from wordcloud import WordCloud

from nltk.tokenize import word_tokenize

import numpy as np
import string

import nltk

patterns = "[0-9!#$%&'()*+,./:;<=>?@[\]^_`{|}~—\"\-]+“”«»…–"

nltk.download('stopwords')

stopWords_eng = set(stopwords.words('english'))
stopWords_rus = set(stopwords.words('russian'))

class TextHandler:

    def make_bagofwords(txt):
            # токенизируем
            txt_tokenized = tokenize(txt)

            # фильтрация
            txt_tokenized_filtered = []
            txt_tokenized_filtered = TextHandler.__filtration_txt(txt_tokenized)

            # лемматизация русская
            txt_lemmatizated = []
            txt_lemmatizated = TextHandler.__lemmatization_rus(txt_tokenized_filtered)

            # лемматизация английская
            txt_lemmatizated = TextHandler.__english_lemmatizer(txt_lemmatizated)

            return txt_lemmatizated

        # определение типа слов на английском слов (сказуемые, существительные и тд)
    def __get_wordnet_pos_for_english(word):
            tag = pos_tag([word])[0][1][0].upper()
            tag_dict = {"J": wordnet.ADJ,
                        "N": wordnet.NOUN,
                        "V": wordnet.VERB,
                        "R": wordnet.ADV}
            return tag_dict.get(tag, wordnet.NOUN)

        # лемматизация английских слов
    def __english_lemmatizer(word_list):
            lemmatizer = WordNetLemmatizer()
            txt_lemmatizated_all = []
            for w in word_list:
                txt_lemmatizated_all.append(lemmatizer.lemmatize(w, TextHandler.__get_wordnet_pos_for_english(w)))

            return txt_lemmatizated_all

        # лемматизация русских слов
    def __lemmatization_rus(txt_tokenized_filtered):
            morph_rus = MorphAnalyzer_rus()

            txt_lemmatizated = []

            for elem in txt_tokenized_filtered:
                elem = elem.strip()
                txt_lemmatizated.append(morph_rus.normal_forms(elem)[0])

            return txt_lemmatizated

    def __filtration_txt(txt_tokenized):
            txt_tokenized_filtered = []

            for w in txt_tokenized:
                w = w.lower()
                if (w not in stopWords_rus) and (w not in stopWords_eng) and (w not in patterns):
                    txt_tokenized_filtered.append(w)

            return txt_tokenized_filtered

class TextHandlerFrequency(TextHandler):
    #количественный анализ - простой и нескольких файлов
    def frequency_analysis(self, textes):
        results = {}
        number = 0
        nltk.download('wordnet')
        for text in textes:
            bag_txt = TextHandler.make_bagofwords(text)
            fdist = FreqDist(bag_txt)
            results["Text" + str(number)] = fdist
            number = number+1
        return results

    # количественный анализ в сравнении содержит файл, который сочетает в себе пересечение слов во всех файлах
    def comparison_frequency_analysis(self, textes):
        results = []
        results_dict = {}
        union_bag = []
        number = 0
        for text in textes:
            t_path = os.path.join(r'D:\FatData-analysis\FatData-analysis\CATsite\files', text)
            file = open(t_path, "r", encoding='utf-8')
            text_from_file = file.read()
            file.close()
            bag_txt = TextHandler.make_bagofwords(text_from_file)
            fdist = FreqDist(bag_txt)
            results_dict["Text" + str(number)] = fdist
            union_bag = union_bag + bag_txt
            number = number+1
        fdist = FreqDist(union_bag)
        results_dict["All_text"] = fdist
        return results_dict

    def comparison_frequency_analysis_str(self, textes):
        results = []
        results_dict = {}
        union_bag = []
        number = 0
        for text in textes:
            bag_txt = TextHandler.make_bagofwords(text)
            fdist = FreqDist(bag_txt)
            results_dict["Text" + str(number)] = fdist
            union_bag = union_bag + bag_txt
            number = number+1
        fdist = FreqDist(union_bag)
        results_dict["All_text"] = fdist
        return results_dict

class TextHandlerSemantic(TextHandler):
    #вес слов - работа с несколькими файлами
    def semantic_analysis(self, textes):
        vectorizer = TfidfVectorizer()

        text_after_work = []
        all_json = {}
        all_df = []
        for text in textes:
            text_from_file = text
            text_from_file = sent_tokenize(text_from_file)
            text_from_file = TextHandlerSemantic.__make_doc_ready_for_tfd(text_from_file)
            text_from_file_line =  ' '.join(text_from_file)
            text_after_work.append(text_from_file_line)

        vectors = vectorizer.fit_transform(text_after_work)
        feature_names = vectorizer.get_feature_names()
        dense = vectors.todense()
        denselist = dense.tolist()
        df = pd.DataFrame(denselist, columns=feature_names)

        str_js = df.to_json(force_ascii=False)
        dict_df = df.to_dict(orient='split')
        return dict_df

    def __make_doc_ready_for_tfd(documents):  #
        for s in range(len(documents)):
            t = documents[s]

            txt_lemmatizated = TextHandler.make_bagofwords(t)

            sentence = ''
            for w in txt_lemmatizated:
                sentence = sentence + w
                sentence = sentence + ' '

            documents[s] = sentence
        return documents

    def __add_sugg(doc1, doc2):
        all_mas = []
        for i in doc1:
            if i in all_mas:
                continue
            else:
                all_mas.append(i)
        for j in doc2:
            if j in all_mas:
                continue
            else:
                all_mas.append(j)
        return all_mas

    # вычисление дистанции между векторами для сравнения
    def dist(x, y):
        return distance.cosine(x, y)

    def get_tf_idf_query_similarity(self, docs):
        vocab = TextHandlerSemantic.__createVocab(docs)

        termDict = {}

        docsTFMat = np.zeros((len(docs), len(vocab)))
        docsIdfMat = np.zeros((len(vocab), len(docs)))

        docTermDf = pd.DataFrame(docsTFMat, columns=sorted(vocab.keys()))
        docCount = 0

        for doc in docs:
            doc = doc.translate(str.maketrans('', '', string.punctuation))
            words = word_tokenize(doc.lower())
            for word in words:
                if (word in vocab.keys()):
                    docTermDf[word][docCount] = docTermDf[word][docCount] + 1

            docCount = docCount + 1

        # Computed idf for each word in vocab
        idfDict = {}

        for column in docTermDf.columns:
            idfDict[column] = np.log((len(docs) + 1) / (1 + (docTermDf[column] != 0).sum())) + 1

        # compute tf.idf matrix
        docsTfIdfMat = np.zeros((len(docs), len(vocab)))
        docTfIdfDf = pd.DataFrame(docsTfIdfMat, columns=sorted(vocab.keys()))

        docCount = 0
        for doc in docs:
            for key in idfDict.keys():
                docTfIdfDf[key][docCount] = docTermDf[key][docCount] * idfDict[key]
            docCount = docCount + 1

        vectorizer = TfidfVectorizer(analyzer='word', norm=None, use_idf=True, smooth_idf=True)
        tfIdfMat = vectorizer.fit_transform(docs)

        feature_names = sorted(vectorizer.get_feature_names())

        docList = []
        number = 0
        for doc in docs:
            docList.append("Doc"+str(number))
            number = number+1

        skDocsTfIdfdf = pd.DataFrame(tfIdfMat.todense(), index=sorted(docList), columns=feature_names)

        csim = cosine_similarity(tfIdfMat, tfIdfMat)

        csimDf = pd.DataFrame(csim, index=sorted(docList), columns=sorted(docList))

        result = csimDf.to_dict(orient='split')

        return result

    def __createVocab(docList):
        vocab = {}
        for doc in docList:
            doc = doc.translate(str.maketrans('', '', string.punctuation))

            words = word_tokenize(doc.lower())
            for word in words:
                if (word in vocab.keys()):
                    vocab[word] = vocab[word] + 1
                else:
                    vocab[word] = 1
        return vocab

class TextHandlerCloud(TextHandler):
    def Str_from_file(self, text):
        t_path = os.path.join(r'D:\FatData-analysis\FatData-analysis\CATsite\files', text)
        file_text = open(t_path, 'r', encoding='utf-8')
        s_t = file_text.read()
        return s_t

    def WordCloud(self, textes):
        TXThandler = TextHandlerCloud()

        StrA = ""
        STRB = []
        for text in textes:
            bag_txt = TextHandler.make_bagofwords(text)
            StrA = " ".join(bag_txt)
            STRB.append(bag_txt)

        wordcloudmas = []
        wordcloud = WordCloud().generate(StrA)
        wordcloudmas.append(wordcloud)

        for i in range(len(textes)):
            STRB_t = " ".join(STRB[i])
            wordcloud = WordCloud().generate(STRB_t)
            wordcloudmas.append(wordcloud)

        return wordcloudmas

