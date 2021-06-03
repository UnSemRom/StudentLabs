// Pages
import NotFound from '@/views/Errors/404'

import AboutCat from '@/views/About/AboutCat'
import TypesAnalytics from '@/views/About/TypesAnalytics'

import QuantitativeАnalysis from '@/views/Analysis/QuantitativeАnalysis'
import SimilarityTexts from '@/views/Analysis/SimilarityTexts'
import WeightWords from '@/views/Analysis/WeightWords'
import WordCloud from '@/views/Analysis/WordCloud'


import PersonalArea from '@/views/PersonalArea/PersonalArea'



const mainNav = [
  {
    path: '/',
    name: 'aboutCat',
    component: AboutCat
  },

  {
    path: '*',
    name: 'notFound',
    component: NotFound
  },
 
  {
    path: '/quantitativeАnalysis',
    name: 'quantitativeАnalysis',
    component: QuantitativeАnalysis
  },
  {
    path: '/similarityTexts',
    name: 'similarityTexts',
    component: SimilarityTexts
  },
  {
    path: '/typesAnalytics',
    name: 'typesAnalytics',
    component: TypesAnalytics
  },
  {
    path: '/weightWords',
    name: 'weightWords',
    component: WeightWords
  },
  {
    path: '/wordCloud',
    name: 'wordCloud',
    component: WordCloud
  },
  {
    path: '/personalArea',
    name: 'personalArea',
    component: PersonalArea
  },  
];

export { mainNav };

