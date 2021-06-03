<template>
  <div id="app">
    <Menu />
    <router-view></router-view>
    <Footer />
    
  </div>
</template>

<script>
import Menu from "@/views/Menu/index.vue";
import Footer from "@/views/Footer/index.vue";

export default {
  name: "App",
  components: {
    Menu,
    Footer
  },
};
</script>

