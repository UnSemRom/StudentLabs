<template>
  <div class="wrapper-content wrapper-content--fixed">
    <section>
      <div class="container">
        <div>
          <img src="@/images/CatSvg7.svg" />
        </div>
        <div>
          <h1 class="glitch" data-text="GLITCH">404</h1>
          <h2>
            Няяяя!!! Страница не найдена. Прейдите на главную старницу
            <router-link class="link" to="/typesAnalytics">main page</router-link>
          </h2>
        </div>
      </div>
    </section>
  </div>
</template>


<style lang="scss" scoped>
@import "@/assets/utils/colors";

.wrapper-content {
  min-height: 80vh;
  display: flex;
  align-items: center;
  justify-content: center;
  text-align: center;
}

.container {
  display: flex;
  justify-content: space-around;
  margin-bottom: 50px;
  align-items: center;
}

h1 {
  font-style: Bold;
  font-size: 288px;
  line-height: 351px;
  line-height: 100%;
  vertical-align: Center;
  color: #d5aae1;
}

h2 {
  font-style: Light;
  font-size: 48px;
  line-height: 59px;
  line-height: 100%;
  vertical-align: Center;
  color: #d5aae1;
}

.glitch {
  color: #d5aae1;
  font-size: 288px;
  position: relative;
  width: 400px;
  margin: 0 auto;
}
@keyframes noise-anim {
  $steps: 20;
  @for $i from 0 through $steps {
    #{percentage($i*(1/$steps))} {
      clip: rect(random(300) + px, 9999px, random(300) + px, 0);
    }
  }
}
.glitch:after {
  content: "404";
  position: absolute;
  left: 2px;
  top: 0;
  text-shadow: -1px 0 red;
  color: #d5aae1;
  background: white;
  overflow: hidden;
  clip: rect(0, 900px, 0, 0);
  animation: noise-anim 2s infinite linear alternate-reverse;
}

@keyframes noise-anim-2 {
  $steps: 20;
  @for $i from 0 through $steps {
    #{percentage($i*(1/$steps))} {
      clip: rect(random(300) + px, 9999px, random(300) + px, 0);
    }
  }
}

.glitch:before {
  content: "404";
  position: absolute;
  left: -2px;
  text-shadow: 1px 0 blue;
  top: 0;
  color: #d5aae1;
  background: white;
  overflow: hidden;
  clip: rect(0, 900px, 0, 0);
  animation: noise-anim-2 3s infinite linear alternate-reverse;
}
</style>
