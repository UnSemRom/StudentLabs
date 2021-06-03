<template>
  <div class="wrapper-content wrapper-content--fixed">
    <section>
      <div class="container">
        <div class="about-cat">
          <div class="center-typing">
            <div class="typing-demo title">
              Clever Analitics Text
            </div>
          </div>
          <p>
            - это аналитический продукт, созданный для упрощения процесса
            проведения исследований, связанных с анализом текстовой информации.
            Его возможности включают в себя:
          <ul>
            <li>количественный контент анализ</li>
            <li>качественный анализ</li>
            <li>сравнительный анализ</li>
            <li>визуализацию ключевых слов с помощью облака слов</li>
          </ul>
          Для проведения исследований больших массивов
          текста не придётся прибегать к написанию кода, аналитик видит
          визуальное представление результатов обработки текста и может сразу
          приступать непосредственно к анализу этих результатов.
          </p>
        </div>
        <div class="cat-6">
        <img src="@/images/CatSvg6.svg" />
              </div>
      </div>

      <div class="container">
        <div class="cat-8">
        <img src="@/images/CatSvg8.svg" />
           </div>
        <div class="list-analysis">
          <p class="BMSTU">Дизайнер</p>
          <p class="BMSTU">Аналитик</p>
          <p class="BMSTU">Разработчик</p>
          <p class="BMSTU">Студенты МГТУ им.Баумана</p>
        </div>
      </div>
    </section>
  </div>
</template>

<style lang="scss" scoped>
@import "@/assets/utils/colors";

.container {
  display: flex;
  justify-content: space-around;
  margin-bottom: 50px;
}

p {
  font-size: 24px;
  line-height: 29px;
  line-height: 100%;
  vertical-align: Top;
  max-width: 700px;
}

.BMSTU {
  margin-top: 120px;
  margin-bottom: 200px;
}

ul {
  margin: 36px;
}

li {
  margin: 24px;
}

.cat-8,
.list-analysis{
   width: 50%;
  padding: 50px;
}

.list-analysis{
  padding-left: 30%;
}

.about-cat{
   width: 50%;
  padding: 1px;
}

.cat-6{
  width: 30%;
}

</style>

<script>
export default {
  name: "AboutCat"
}
</script>